#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"
#include "Utilities/Timer.h"
//#include "PinnedVector.h"
#include <cmath>
#include <random>
#include <Material/PhongMaterial.h>
#include <Math/Random.h>

#define SSAA 1
#define SAMPLESIZE 4
#define BOUNCES 3

Vector3 Renderer::s_BackgroundColor;
Vector3 Renderer::s_AmbientColor;
Vector3 Renderer::s_GlobalColor;
Group Renderer::s_scene;
std::vector<DirectionalLight> Renderer::s_lights;
std::vector<PhongMaterial> Renderer::s_materials;
uint64_t Renderer::s_epoch = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();

/*Java-like instanceof function (Thanks stackoverflow.com)*/
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

inline u32 ConvertToRGBA(const Vector3& v) {
    const u8 r = static_cast<u8>(v.get_r() * 255);
    const u8 g = static_cast<u8>(v.get_g() * 255);
    const u8 b = static_cast<u8>(v.get_b() * 255);
    const u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

inline u32 ConvertToRGBA(const Vector4& v) {
    const u8 r = static_cast<u8>(v.get_r() * 255);
    const u8 g = static_cast<u8>(v.get_g() * 255);
    const u8 b = static_cast<u8>(v.get_b() * 255);
    const u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

inline Vector3 reflect(const Vector3& I, const Vector3& N) {
    return I - 2 * I.dot(N) * N;
}

inline Vector3 refract(const Vector3& V, const Vector3& N, f32 etai_over_etat) {
    const Vector3 uv = -V;
    const f32 cos_theta = fmin(uv.dot(N), 1.0f);
    const Vector3 r_out_perp =  etai_over_etat * (uv + cos_theta * N);
    const Vector3 r_out_parallel = -sqrtf(std::fabs(1.0f - r_out_perp.length2())) * N;
    return r_out_perp + r_out_parallel;
}

inline f32 reflectance(f32 cosine, f32 refraction_index) {
    // Use Schlick's approximation for reflectance.
    f32 r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*powf((1 - cosine),5);
}

inline f32 random_float() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return static_cast<f32>(distribution(generator));
}

inline f32 randomFloat(uint64_t& seed) {
    seed = PCG_Hash(seed);
    return static_cast<f32>(seed) / (f32)std::numeric_limits<uint64_t>::max();
}

inline Vector3 sample_square(uint64_t& seed) {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vector3(randomFloat(seed), randomFloat(seed), 0.0f);
}

void Renderer::Render(const std::string& filename, const std::shared_ptr<Camera>& camera, f32 near, f32 far, bool monochrome) {
    m_Near = near;
    m_Far = far;
    m_Image.m_data.clear();
    m_ImageDepth.m_data.clear();
    m_Image.init(Renderer::s_BackgroundColor);
    m_ImageDepth.init(Renderer::s_BackgroundColor);
    m_Filename = filename;
    Timer timer;

    for(u32 y = 0; y < m_Height; ++y){
        #pragma omp parallel for schedule(dynamic) num_threads(16)
        for(u32 x = 0; x < m_Width; ++x){
            s_fragment(x, y, m_Width, m_Height, !monochrome, camera);
        }
    }
    std::cout << "Finished Rendering " << m_Filename << " in ";
    timer.Stop();

    //s_save(filename + "_depth.png", monochrome);
    s_save(filename + ".png", !monochrome);
}

void Renderer::s_save(const std::string& path, bool monochrome) const {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path .c_str(), static_cast<i32>(m_Width), static_cast<i32>(m_Height), 4, m_Image.m_data.data(), static_cast<i32>(m_Width) * 4);
    /*
    if(monochrome) {
        stbi_write_png(path .c_str(), m_Width, m_Height, 4, s_ImageDepth.m_data.data(), m_Width*4);
    }
    else {
        stbi_write_png(path .c_str(), static_cast<i32>(m_Width), static_cast<i32>(m_Height), 4, s_Image.m_data.data(), static_cast<i32>(m_Width) * 4);
    }
    */
}

inline void Renderer::s_fragment(const u32 x, const u32 y, const u32 width, const u32 height, bool monochrome, const std::shared_ptr<Camera>& camera) {
    Vector3 pixelColor;
    thread_local Hit hit;
    uint64_t localSeed = Renderer::s_epoch;
    u32 lx = x;
    u32 ly = y;
    hit.m_Id = -1;
    hit.set_t(m_Far);
#if SSAA
    for(u32 s = 0; s < SAMPLESIZE; ++s) {
        Vector3 sampleArea = sample_square(localSeed);
        sampleArea.normalize();
        f32 nx = (static_cast<f32>(lx) + sampleArea.get_x())/static_cast<f32>(width);
        f32 ny = (static_cast<f32>(ly) + sampleArea.get_y())/static_cast<f32>(height);
        Ray ray = camera->generateRay(nx, ny);
        pixelColor = pixelColor + traceRay(ray, m_Near, BOUNCES, 1.0, 1.0, hit);
    }
    pixelColor = pixelColor / SAMPLESIZE;
#else
    f32 nx = (static_cast<f32>(x))/static_cast<f32>(width);
    f32 ny = (static_cast<f32>(y))/static_cast<f32>(height);
    Ray ray = camera->generateRay(nx, ny);
    pixelColor = traceRay(ray, m_Near, 3, 1.0, 1.0, hit);

#endif
    pixelColor.clamp();
    /* if no hit, draw background colors */
    if(hit.get_t() == m_Far) {
        //s_ImageDepth.set_pixel(nx, ny, ConvertToRGBA(bg));
        m_Image.set_pixel(lx, ly, ConvertToRGBA(s_GlobalColor));
        return;
    }

    /* otherwise draw object's colors */
    m_Image.set_pixel(lx, ly, ConvertToRGBA(pixelColor));

    /* if monochrome, draw depth data */
    /*
    if (monochrome) {
        f32 depth = (s_Far - hit.get_t()) / (s_Far - s_Near);
        s_ImageDepth.set_pixel(nx, ny, ConvertToRGBA(Vector3(depth, depth, depth)));
        return;
    }
    */

}

Vector3 Renderer::traceRay(const Ray &ray, const f32 tmin, const i32 bounces, const f32 weight, f32 indexOfRefraction, Hit& hit) {
    /* Recursion depth limit */
    if(bounces <= 0 || weight < 0.1) {
        return {0.0, 0.0, 0.0};
    }

    /* check for ray intersection with scene m_objects */
    if(!s_scene.intersect(ray, hit, tmin, m_Far)) {
        return {0.0, 0.0, 0.0};
    }

    /* normalize surface normal vector */
    hit.m_Normal.normalize();

    /* retrieve material */
    PhongMaterial material = Renderer::s_materials.at(hit.m_MaterialIndex);
    Vector3 rgb = {0.0, 0.0, 0.0};

    /* Shoot out ray for every light */
    for(const auto& light : Renderer::s_lights) {
        /* Object occluded by another object */
        Ray shadowRay = Ray(hit.m_Point , -light.m_Direction);
        Hit shadowHit = Hit();
        bool isInShadow = s_scene.inShadow(shadowRay, shadowHit, hit, FLT_EPSILON, m_Far);
        if(!isInShadow) {
            rgb = rgb + material.shade(ray, hit, light);
        }

        Vector3 correctedNormal = hit.m_Normal;

        /* Transparent Object */
        if(material.m_IsTransparent) {
            f32 correctedRefractionIndex = hit.m_OutwardNormal ? (1.0f/material.m_IndexOfRefraction) : material.m_IndexOfRefraction;
            correctedNormal = hit.m_OutwardNormal ? hit.m_Normal : -hit.m_Normal;
            Vector3 transmittanceDirection = ray.m_direction.getVec3();
            Vector3 nTransmittanceDirection = -transmittanceDirection;
            transmittanceDirection.normalize();
            nTransmittanceDirection.normalize();

            const f32 totalInternalReflection = sqrtf(1 - (correctedRefractionIndex*correctedRefractionIndex) * (1 - powf(hit.m_Normal.dot(transmittanceDirection), 2.0f)));

            //f32 cos_theta = fmin(nTransmittanceDirection.dot(hit.m_Normal), 1.0);
            const bool canRefract = totalInternalReflection > 0.0f;
            Vector3 refractedVector;

            // Hollow glass sphere -> || reflectance(cos_theta, correctedRefractionIndex) > random_float()
            if(!canRefract) {
                refractedVector = reflect(transmittanceDirection, hit.m_Normal);
            }
            else {
                refractedVector = (correctedRefractionIndex * (hit.m_Normal.dot(transmittanceDirection)) - totalInternalReflection) * hit.m_Normal - correctedRefractionIndex * transmittanceDirection;
            }

            refractedVector.normalize();

            Ray transmittedRay = Ray(hit.m_Point, refractedVector);
            Hit transmittedHit = Hit();
            rgb = rgb + material.m_TransparentColor * traceRay(transmittedRay, FLT_EPSILON, bounces-1, weight, material.m_IndexOfRefraction, transmittedHit);
        }

        /* Reflective Object */
        if(material.m_IsReflective) {
            Vector3 reflectVector = reflect(ray.m_direction.getVec3(), hit.m_Normal);
            Ray reflectRay = Ray(hit.m_Point + correctedNormal * 0.0001, reflectVector);
            Hit reflectHit = Hit();
            rgb = rgb + material.m_ReflectiveColor * traceRay(reflectRay, FLT_EPSILON, bounces-1, weight, material.m_IndexOfRefraction, reflectHit);
        }

    }
    return rgb;
}
