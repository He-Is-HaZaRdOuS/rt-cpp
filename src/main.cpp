#define DOCTEST_CONFIG_IMPLEMENT
#define PIXELCOUNT 1024

#include "Utilities/Macros.h"
#include "Utilities/Timer.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include <Material/PhongMaterial.h>
#include "Math/Random.h"
#include "Beam/Ray.h"
#include "Beam/Hit.h"
#include "Camera/Camera.h"
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "Geometry/Object3D.h"
#include "Geometry/Sphere.h"
#include "Geometry/Group.h"
#include "Geometry/Triangle.h"
#include "Geometry/Transform.h"
#include "Geometry/Plane.h"
#include <Geometry/Cylinder.h>
#include "Renderer/Image.h"
#include "Renderer/Renderer.h"
#include "Renderer/Light.h"
#include "Doctest/doctest.h"

#include <cmath>
#include <iostream>

void init(Renderer& renderer, std::shared_ptr<Camera>& camera, const std::string& path);
std::shared_ptr<Camera> collectCamera(const json &data);
void collectBackground(const json &data, Renderer &renderer);
std::vector<DirectionalLight> collectLight(const json &data);
Group collectScene(const json &data);
std::vector<PhongMaterial> collectMaterial(const json &data);

int main() {
/*
    doctest::Context context;

    const int res = context.run();

    return res;
*/
    /* JSON filenames are provided without the extension */
    std::string file1 = "scene1_exponent_variations";
    std::string file2 = "scene2_plane_sphere";
    std::string file3 = "scene3_colored_lights";
    std::string file4 = "scene4_reflective_sphere";
    std::string file5 = "scene5_transparent_sphere";
    std::string file6 = "scene6_transparent_sphere2";
    std::string file7 = "scene7_cylinder";
    std::string file8 = "scene8_balls";

    /* Construct necessary m_objects */
    std::shared_ptr<Camera> camera_ptr;
    Renderer renderer = Renderer(PIXELCOUNT, PIXELCOUNT);

    std::cout << "STARTING GLOBAL TIMER!!!" << std::endl;
    Timer timer;

    /* init m_objects and render scenes */

    init(renderer, camera_ptr,  file1);
    renderer.Render(file1, camera_ptr,  2, 40, true);

    init(renderer, camera_ptr,  file2);
    renderer.Render(file2, camera_ptr,  2, 40, true);

    init(renderer, camera_ptr, file3);
    renderer.Render(file3, camera_ptr, 2, 40, true);

    init(renderer, camera_ptr, file4);
    renderer.Render(file4, camera_ptr, 2, 8, true);

    init(renderer, camera_ptr, file5);
    renderer.Render(file5, camera_ptr, 2, 40, true);

    init(renderer, camera_ptr, file6);
    renderer.Render(file6, camera_ptr, 2, 40, true);

    init(renderer, camera_ptr, file7);
    renderer.Render(file7, camera_ptr, 2, 16, true);

    init(renderer, camera_ptr, file8);
    renderer.Render(file8, camera_ptr, 2, 40, true);

    std::cout << "STOPPING GLOBAL TIMER!!!" << std::endl;
    timer.Stop();

    return 0;
}

std::shared_ptr<Camera> collectCamera(const json &data) {
    u32 index;
    f32 buffer[3];

    std::shared_ptr<OrthographicCamera> orthocamera_ptr = std::make_shared<OrthographicCamera>();

    if(data.contains("orthocamera")) {
        try {
            const auto orthocamera = data.find("orthocamera");
            {
                index = 0;
                for(const auto& component : *orthocamera->find("center")){
                    //std::cout << component << "\n";
                    buffer[index++] = component;
                }
                orthocamera_ptr->m_center = Vector4(buffer[0], buffer[1], buffer[2], 1.0);
            }

            {
                index = 0;
                for(const auto& component : *orthocamera->find("direction")){
                    //std::cout << component << "\n";
                    buffer[index++] = component;
                }
                orthocamera_ptr->m_direction = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
            }

            {
                index = 0;
                for(const auto& component : *orthocamera->find("up")){
                    //std::cout << component << "\n";
                    buffer[index++] = component;
                }
                orthocamera_ptr->m_up = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
            }

            {
                const auto s = orthocamera->find("size")->dump();
                orthocamera_ptr->m_size = stof(s);
                //std::cout << s;
            }
            /* calculate horizontal vector */
            orthocamera_ptr->m_horizontal = orthocamera_ptr->m_direction.cross_zero( orthocamera_ptr->m_up);

            return orthocamera_ptr;
        }
        catch (...)
        {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"orthocamera\"\n";
        }
    }

    std::shared_ptr<PerspectiveCamera> perspcam_ptr = std::make_shared<PerspectiveCamera>();
    if(data.contains("perspectivecamera")){
        const auto perspectivecamera = data.find("perspectivecamera");
        try {
                {
                    index = 0;
                    for(const auto& component : *perspectivecamera->find("center")){
                        //std::cout << component << "\n";
                        buffer[index++] = component;
                    }
                    perspcam_ptr->m_center = Vector4(buffer[0], buffer[1], buffer[2], 1.0);
                }

                {
                    index = 0;
                    for(const auto& component : *perspectivecamera->find("direction")){
                        //std::cout << component << "\n";
                        buffer[index++] = component;
                    }
                    perspcam_ptr->m_direction = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
                }

                {
                    index = 0;
                    for(const auto& component : *perspectivecamera->find("up")){
                        //std::cout << component << "\n";
                        buffer[index++] = component;
                    }
                    perspcam_ptr->m_up = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
                }

                {
                    auto s = perspectivecamera->find("angle")->dump();
                    perspcam_ptr->m_angle = stof(s);
                    //std::cout << s;
                }
                /* calculate horizontal vector */
                perspcam_ptr->m_horizontal = perspcam_ptr->m_direction.cross_zero( perspcam_ptr->m_up);
                perspcam_ptr->m_scale = static_cast<f32>(1.0 / std::tan((perspcam_ptr->m_angle * M_PI / 180.0) * 0.5));

                return perspcam_ptr;
        }
        catch (...)
        {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"perspectivecamera\"\n";
        }
    }

    /* no camera found */
    std::cerr << "NO CAMERA FOUND \n";
    exit(1);
}

void collectBackground(const json &data, Renderer &renderer) {
    u32 index;
    f32 buffer[3];

    if(data.contains("background")){
        try {
            auto background = data.find("background");

            {
                index = 0;
                for(const auto& n : *background->find("color")){
                    //std::cout << n << "\n";
                    buffer[index++] = n;
                }
                Renderer::s_BackgroundColor = Vector3(buffer[0], buffer[1], buffer[2]);
            }

            {
                index = 0;
                for(const auto& n : *background->find("ambient")){
                    //std::cout << n << "\n";
                    buffer[index++] = n;
                }
                Renderer::s_AmbientColor = Vector3(buffer[0], buffer[1], buffer[2]);
            }

            Renderer::s_GlobalColor = Renderer::s_BackgroundColor * Renderer::s_AmbientColor;

        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"background\"\n";
            exit(1);
        }
    }
}

std::vector<DirectionalLight> collectLight(const json &data) {
    u32 index;
    f32 buffer[3];
    std::vector<DirectionalLight> s_lights;

    if(data.contains("lights")) {
        try {
            const auto lights = data.find("lights");
            for(const auto& n : *lights) {
                //std::cout << n << "\n";
                if(n.contains("directionalLight")) {
                    DirectionalLight dl = DirectionalLight();
                    const auto dLight = n.find("directionalLight");
                    const auto direction = dLight->find("direction");
                    const auto color = dLight->find("color");

                    {
                        index = 0;
                        for(const auto& d : *direction){
                            buffer[index++] = d;
                        }
                        dl.m_Direction.set_r(buffer[0]);
                        dl.m_Direction.set_g(buffer[1]);
                        dl.m_Direction.set_b(buffer[2]);
                    }

                    {
                        index = 0;
                        for(const auto& c : *color){
                            buffer[index++] = c;
                        }
                        dl.m_Color.set_r(buffer[0]);
                        dl.m_Color.set_g(buffer[1]);
                        dl.m_Color.set_b(buffer[2]);
                    }
                    s_lights.push_back(dl);
                }

            }
        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"light\"\n";
            exit(1);
        }
    } else if(data.contains("light")) {
        try {
            DirectionalLight s_light;
            const auto light = data.find("light");

            {
                index = 0;
                for(const auto& n : *light->find("direction")){
                    buffer[index++] = n;
                }
                s_light.m_Direction.set_r(buffer[0]);
                s_light.m_Direction.set_g(buffer[1]);
                s_light.m_Direction.set_b(buffer[2]);
            }

            {
                index = 0;
                for(const auto& n : *light->find("color")){
                    buffer[index++] = n;
                }
                s_light.m_Color.set_r(buffer[0]);
                s_light.m_Color.set_g(buffer[1]);
                s_light.m_Color.set_b(buffer[2]);
            }

            s_lights.push_back(s_light);
        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"light\"\n";
            exit(1);
        }
    }
    return s_lights;
}

Group collectScene(const json &data) {
    u32 index;
    f32 buffer[3];
    f32 v1_buf[3];
    f32 v2_buf[3];
    f32 v3_buf[3];
    i32 id = 0;
    Group scene = Group();

    if(data.contains("group")) {
        try {
            const auto group = data.find("group");
            {
                for (const auto& n : *group){
                    if(n.contains("sphere")){
                        //std::cout << n << "\n";
                        auto const& sphere = n.find("sphere");
                        auto const& center = sphere->find("center");
                        auto const& radius = sphere->find("radius");
                        auto const& material = sphere->find("material");

                        index = 0;
                        for(auto const& p : *center){
                            buffer[index++] = p;
                        }

                        auto r = radius->dump();
                        std::shared_ptr<Sphere> sp0 = std::make_shared<Sphere>(Sphere(stof(r), {buffer[0], buffer[1], buffer[2], 1.0}));

                        auto m = material->dump();
                        sp0->m_MaterialIndex = stoi(m);
                        sp0->m_Id = id++;

                        scene.m_objects.push_back(sp0);
                    }

                    if(n.contains("cylinder")){
                        //std::cout << n << "\n";
                        auto const& cylinder = n.find("cylinder");
                        auto const& center = cylinder->find("center");
                        auto const& axis = cylinder->find("axis");
                        auto const& radius = cylinder->find("radius");
                        auto const& height = cylinder->find("height");
                        auto const& material = cylinder->find("material");

                        std::shared_ptr<Cylinder> c0 = std::make_shared<Cylinder>(Cylinder());

                        index = 0;
                        for(auto const& p : *center){
                            buffer[index++] = p;
                        }
                        c0->m_center = {buffer[0], buffer[1], buffer[2]};

                        index = 0;
                        for(auto const& p : *axis){
                            buffer[index++] = p;
                        }

                        c0->m_axis = {buffer[0], buffer[1], buffer[2]};

                        auto r = radius->dump();
                        auto h = height->dump();

                        c0->m_radius = stof(r);
                        c0->m_height = stof(h);

                        auto m = material->dump();
                        c0->m_MaterialIndex = stoi(m);
                        c0->m_Id = id++;

                        scene.m_objects.push_back(c0);
                    }

                    if(n.contains("triangle")){
                        //std::cout << n << "\n";
                        auto const& triangle = n.find("triangle");
                        auto const& v1 = triangle->find("v1");
                        auto const& v2 = triangle->find("v2");
                        auto const& v3 = triangle->find("v3");
                        auto const& material = triangle->find("material");

                        index = 0;
                        for(auto const& p : *v1){
                            v1_buf[index++] = p;
                        }

                        index = 0;
                        for(auto const& p : *v2){
                            v2_buf[index++] = p;
                        }

                        index = 0;
                        for(auto const& p : *v3){
                            v3_buf[index++] = p;
                        }

                        auto m = material->dump();

                        //TODO
                        // Make a shared_ptr<Triangle> and add it to scene vector
                        std::shared_ptr<Triangle> tr0 = std::make_shared<Triangle>(Triangle({v1_buf[0], v1_buf[1], v1_buf[2]},
                                                                                            {v2_buf[0], v2_buf[1], v2_buf[2]},
                                                                                            {v3_buf[0], v3_buf[1], v3_buf[2]}));
                        tr0->m_MaterialIndex = std::stoi(m);
                        tr0->m_Id = id++;
                        Vector4 normal0 = {tr0->m_v2.cross_zero(tr0->m_v3)};
                        tr0->m_normal = {normal0.get_x(), normal0.get_y(), normal0.get_z()};
                        scene.m_objects.push_back(tr0);

                    }

                    if(n.contains("plane")){
                        //std::cout << n << "\n";
                        auto const& plane = n.find("plane");
                        auto const& normal = plane->find("normal");
                        auto const& material = plane->find("material");
                        auto const& offset = plane->find("offset");

                        index = 0;
                        for(auto const& p : *normal){
                            v1_buf[index++] = p;
                        }

                        auto d = offset->dump();

                        //TODO
                        // Make a shared_ptr<Plane> and add it to scene vector
                        std::shared_ptr<Plane> p0 = std::make_shared<Plane>(Plane());
                        auto m = material->dump();
                        p0->m_MaterialIndex = std::stoi(m);
                        p0->m_Id = id++;
                        p0->m_d = stof(d);
                        p0->m_normal = {v1_buf[0], v1_buf[1], v1_buf[2]};
                        scene.m_objects.push_back(p0);

                    }

                    if(n.contains("transform")){
                        std::shared_ptr<Transform> t0 = std::make_shared<Transform>(Transform());
                        auto const& transform = n.find("transform");
                        if(transform->contains("transformations")) {
                            auto const& transformations0 = transform->find("transformations");
                            for(auto const& transformations: *transformations0) {
                                if(transformations.contains("translate")) {
                                    auto const& translate = transformations.find("translate");
                                    index = 0;
                                    for(auto const& p : *translate){
                                        buffer[index++] = p;
                                    }
                                    Matrix4 t = Matrix4::Translate(buffer[0], buffer[1], buffer[2]);
                                    Vector4 v = Vector4(buffer[0], buffer[1], buffer[2]);
                                    t0->m_translate = t;
                                    t0->m_translateOffset = v;
                                }

                                if(transformations.contains("zrotate")) {
                                    auto const &zrotate = transformations.find("zrotate");
                                    auto z = zrotate->dump();
                                    Matrix4 t = Matrix4::RotateZ(stof(z));
                                    t0->m_rotatez = t;
                                }

                                if(transformations.contains("yrotate")) {
                                    auto const &yrotate = transformations.find("yrotate");
                                    auto y = yrotate->dump();
                                    Matrix4 t = Matrix4::RotateY(stof(y));
                                    t0->m_rotatey = t;
                                }

                                if(transformations.contains("xrotate")) {
                                    auto const& xrotate = transformations.find("xrotate");
                                    auto x = xrotate->dump();
                                    Matrix4 t = Matrix4::RotateX(stof(x));
                                    t0->m_rotatex = t;
                                }

                                if(transformations.contains("scale")) {
                                    //std::cout <<"ype";
                                    auto const& scale = transformations.find("scale");
                                    index = 0;
                                    for(auto const& p : *scale){
                                        buffer[index++] = p;
                                    }
                                    Matrix4 t = Matrix4::Scale(buffer[0], buffer[1], buffer[2]);
                                    t0->m_scale = t;
                                    t0->m_scaleOffset = Vector4(buffer[0], buffer[1], buffer[2]);
                                }
                                // SRT

                                t0->m_transform = t0->m_transform.mult(t0->m_scale);
                                t0->m_transform = t0->m_transform.mult(t0->m_rotatex);
                                t0->m_transform = t0->m_transform.mult(t0->m_rotatey);
                                t0->m_transform = t0->m_transform.mult(t0->m_rotatez);
                                t0->m_transform = t0->m_transform.mult(t0->m_translate);

                                t0->m_transform = t0->m_transform.inverse();
                                t0->m_transform_normal = t0->m_transform.transpose();

                            }

                        }

                        if(transform->contains("object")){
                            auto const& obj0 = transform->find("object");

                            if(obj0->contains("sphere")){
                                //std::cout << n << "\n";
                                auto const& sphere = obj0->find("sphere");
                                auto const& center = sphere->find("center");
                                auto const& radius = sphere->find("radius");
                                auto const& material = sphere->find("material");

                                index = 0;
                                for(auto const& p : *center){
                                    buffer[index++] = p;
                                }

                                auto r = radius->dump();
                                std::shared_ptr<Sphere> sp0 = std::make_shared<Sphere>(Sphere(stof(r), {buffer[0], buffer[1], buffer[2], 1.0}));

                                auto m = material->dump();
                                sp0->m_MaterialIndex = stoi(m);
                                t0->m_object = sp0;
                            }

                            if(obj0->contains("cylinder")){
                                //std::cout << n << "\n";
                                auto const& cylinder = obj0->find("cylinder");
                                auto const& center = cylinder->find("center");
                                auto const& axis = cylinder->find("axis");
                                auto const& radius = cylinder->find("radius");
                                auto const& height = cylinder->find("height");
                                auto const& material = cylinder->find("material");

                                std::shared_ptr<Cylinder> c0 = std::make_shared<Cylinder>(Cylinder());

                                index = 0;
                                for(auto const& p : *center){
                                    buffer[index++] = p;
                                }
                                c0->m_center = {buffer[0], buffer[1], buffer[2]};

                                index = 0;
                                for(auto const& p : *axis){
                                    buffer[index++] = p;
                                }

                                c0->m_axis = {buffer[0], buffer[1], buffer[2]};

                                auto r = radius->dump();
                                auto h = height->dump();

                                c0->m_radius = stof(r);
                                c0->m_height = stof(h);

                                auto m = material->dump();
                                c0->m_MaterialIndex = stoi(m);
                                c0->m_Id = id++;

                                t0->m_object = c0;
                            }

                            if(obj0->contains("triangle")){
                                //std::cout << n << "\n";
                                auto const& triangle = obj0->find("triangle");
                                auto const& v1 = triangle->find("v1");
                                auto const& v2 = triangle->find("v2");
                                auto const& v3 = triangle->find("v3");
                                auto const& material = triangle->find("material");

                                index = 0;
                                for(auto const& p : *v1){
                                    v1_buf[index++] = p;
                                }

                                index = 0;
                                for(auto const& p : *v2){
                                    v2_buf[index++] = p;
                                }

                                index = 0;
                                for(auto const& p : *v3){
                                    v3_buf[index++] = p;
                                }

                                //TODO
                                // Make a shared_ptr<Triangle> and add it to scene vector
                                std::shared_ptr<Triangle> tr0 = std::make_shared<Triangle>(Triangle({v1_buf[0], v1_buf[1], v1_buf[2]},
                                                                                                    {v2_buf[0], v2_buf[1], v2_buf[2]},
                                                                                                    {v3_buf[0], v3_buf[1], v3_buf[2]}));
                                auto m = material->dump();
                                tr0->m_MaterialIndex = stoi(m);
                                Vector4 normal0 = {tr0->m_v2.cross_zero(tr0->m_v3)};
                                tr0->m_normal = {normal0.get_x(), normal0.get_y(), normal0.get_z()};
                                t0->m_object = tr0;

                            }

                            if(obj0->contains("plane")){
                                //std::cout << n << "\n";
                                auto const& plane = obj0->find("plane");
                                auto const& normal = plane->find("normal");
                                auto const& material = plane->find("material");
                                auto const& offset = plane->find("offset");

                                index = 0;
                                for(auto const& p : *normal){
                                    v1_buf[index++] = p;
                                }

                                auto d = offset->dump();

                                //TODO
                                // Make a shared_ptr<Plane> and add it to scene vector
                                std::shared_ptr<Plane> p0 = std::make_shared<Plane>(Plane());
                                auto m = material->dump();
                                p0->m_MaterialIndex = std::stoi(m);
                                p0->m_d = stof(d);
                                p0->m_normal = {v1_buf[0], v1_buf[1], v1_buf[2]};
                                t0->m_object = p0;

                            }
                        }
                        t0->m_Id = id++;
                        scene.m_objects.push_back(t0);

                    }
                }
            }
        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"group\"\n";
            exit(1);
        }
    }
    return scene;
}

std::vector<PhongMaterial> collectMaterial(const json &data) {
    u32 index;
    f32 buffer[3];
    std::vector<PhongMaterial> phongs = std::vector<PhongMaterial>();

    if(data.contains("materials")) {
        const auto materials = data.find("materials");
        for(const auto& n : *materials) {
            //std::cout << n << "\n";
            if(n.contains("phongMaterial")) {
                auto const& phong = n.find("phongMaterial");
                auto const& diffuse = phong->find("diffuseColor");

                PhongMaterial pm = PhongMaterial();

                index = 0;
                for(auto const& p : *diffuse){
                    buffer[index++] = p;
                }
                pm.m_DiffuseColor = {buffer[0], buffer[1], buffer[2]};

                if(phong->contains("specularColor")) {
                    auto const& specular = phong->find("specularColor");


                    index = 0;
                    for(auto const& p : *specular) {
                        buffer[index++] = p;
                    }
                    pm.m_SpecularColor = {buffer[0], buffer[1], buffer[2]};
                }

                if(phong->contains("exponent")) {
                    auto const& e = phong->find("exponent");

                    auto const& exp = e->dump();
                    pm.m_ExponentValue = stof(exp);
                }

                if(phong->contains("transparentColor")) {
                    auto const& transparent = phong->find("transparentColor");

                    index = 0;
                    for(auto const& t : *transparent) {
                        buffer[index++] = t;
                    }
                    pm.m_TransparentColor = {buffer[0], buffer[1], buffer[2]};
                    if(pm.m_TransparentColor.get_x() > 0.0 || pm.m_TransparentColor.get_y() > 0.0 || pm.m_TransparentColor.get_z() > 0.0)
                        pm.m_IsTransparent = true;
                    else
                        pm.m_IsTransparent = false;
                }
                else {
                    pm.m_IsTransparent = false;
                }

                if(phong->contains("reflectiveColor")) {
                    auto const& reflective = phong->find("reflectiveColor");

                    index = 0;
                    for(auto const& r : *reflective) {
                        buffer[index++] = r;
                    }
                    pm.m_ReflectiveColor = {buffer[0], buffer[1], buffer[2]};
                    if(pm.m_ReflectiveColor.get_x() > 0.0 || pm.m_ReflectiveColor.get_y() > 0.0 || pm.m_ReflectiveColor.get_z() > 0.0)
                        pm.m_IsReflective = true;
                    else
                        pm.m_IsReflective = false;
                }
                else {
                    pm.m_IsReflective = false;
                }

                if(phong->contains("indexOfRefraction")) {
                    auto const& ior = phong->find("indexOfRefraction");

                    auto const& q = ior->dump();
                    pm.m_IndexOfRefraction = stof(q);
                }

                phongs.push_back(pm);
            }
        }
    }
    return phongs;
}

/* init m_objects with scene data */
void init(Renderer& renderer, std::shared_ptr<Camera>& camera, const std::string& path){
    std::ifstream f(RESOURCES_PATH + path + ".json");
    const json data = json::parse(f);
    Renderer r = Renderer(PIXELCOUNT, PIXELCOUNT);
    camera = collectCamera(data);
    collectBackground(data, r);
    Renderer::s_scene.m_objects.clear();
    Renderer::s_lights.clear();
    Renderer::s_materials.clear();
    Renderer::s_scene = collectScene(data);
    Renderer::s_lights = collectLight(data);
    Renderer::s_materials = collectMaterial(data);
    renderer = r;
}
