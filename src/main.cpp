#include <iostream>

#include "Utilities/Macros.h"
#include "Utilities/Timer.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Random.h"
#include "Beam/Ray.h"
#include "Beam/Hit.h"
#include "Camera/Camera.h"
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "Geometry/Object3D.h"
#include "Geometry/Sphere.h"
#include "Geometry/Group.h"
#include "Renderer/Image.h"
#include "Renderer/Renderer.h"
#include "Renderer/Light.h"

void init(Renderer& renderer, std::shared_ptr<Camera>& camera, Group& scene, Light &light, const std::string& path);
std::shared_ptr<Camera> collectCamera(const json &data);
void collectBackground(const json &data, Renderer &renderer);
Light collectLight(const json &data);
void collectScene(const json &data, Group &scene);


int main() {
    /* Start timer to measure program running time */
    Timer timer;

    /* JSON filenames are provided without the extension */
    std::string file1 = "scene3_perspective";
    std::string file2 = "scene2";

    /* Construct necessary objects */
    std::shared_ptr<Camera> camera_ptr;
    Renderer renderer = Renderer(512, 512);
    Group scene = Group();
    Light light = Light();

    /* init objects and render scenes */
    init(renderer, camera_ptr, scene, light, file1);
    renderer.Render(file1, camera_ptr, scene, light, 8, 11.5, true);
    //renderer.Render(file1, camera, scene, 9, 11, true);

    //init(renderer, camera, scene, file2);
    //renderer.Render(file2, camera, scene, 8, 11.5, true);
    //renderer.Render(file2, camera, scene, 8, 11.5, true);

    return 0;
}

std::shared_ptr<Camera> collectCamera(const json &data) {
    u32 index;
    f32 buffer[3];

    std::shared_ptr<OrthographicCamera> orthocamera_ptr = std::make_shared<OrthographicCamera>();

    if(data.contains("orthocamera")) {
        try {
            auto orthocamera = data.find("orthocamera");
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
                auto s = orthocamera->find("size")->dump();
                orthocamera_ptr->m_size = stoi(s);
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
        auto perspectivecamera = data.find("perspectivecamera");
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
                perspcam_ptr->m_scale = (f32)tan((perspcam_ptr->m_angle) * (M_PI / 180));

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

    if(data.contains("background")){
        try {
            auto background = data.find("background");

            {
                index = 0;
                for(const auto& n : *background->find("color")){
                    //std::cout << n << "\n";
                    renderer.m_background_color[index++] = n;
                }
            }

            {
                index = 0;
                for(const auto& n : *background->find("ambient")){
                    //std::cout << n << "\n";
                    renderer.m_ambient_color[index++] = n;
                }
            }

        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"background\"\n";
            exit(1);
        }
    }
}

Light collectLight(const json &data) {
    u32 index;
    f32 buffer[3];

    if(data.contains("light")) {
        Light s_light;
        try {
            auto light = data.find("light");

            {
                index = 0;
                for(const auto& n : *light->find("direction")){
                    buffer[index++] = n;
                }
                s_light.m_direction.set_r(buffer[0]);
                s_light.m_direction.set_g(buffer[1]);
                s_light.m_direction.set_b(buffer[2]);
            }

            {
                index = 0;
                for(const auto& n : *light->find("color")){
                    buffer[index++] = n;
                }
                s_light.m_color.set_r(buffer[0]);
                s_light.m_color.set_g(buffer[1]);
                s_light.m_color.set_b(buffer[2]);
            }

            return s_light;
        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"light\"\n";
            exit(1);
        }
    }

}

void collectScene(const json &data, Group &scene) {
    u32 index;
    f32 buffer[3];
    f32 v1_buf[3];
    f32 v2_buf[3];
    f32 v3_buf[3];

    if(data.contains("group")) {
        try {
            auto group = data.find("group");
            {
                scene.objects.clear();
                for (const auto& n : *group){
                    if(n.contains("sphere")){
                        std::cout << n << "\n";
                        auto const& sphere = n.find("sphere");
                        auto const& center = sphere->find("center");
                        auto const& radius = sphere->find("radius");
                        auto const& color = sphere->find("color");

                        index = 0;
                        for(auto const& p : *center){
                            buffer[index++] = p;
                        }

                        auto r = radius->dump();
                        std::shared_ptr<Sphere> sp0 = std::make_shared<Sphere>(Sphere(stof(r), {buffer[0], buffer[1], buffer[2], 1.0}));

                        index = 0;
                        for(auto const& c : *color){
                            buffer[index++] = c;
                        }

                        sp0->set_color(buffer);
                        scene.objects.push_back(sp0);
                    }

                    if(n.contains("triangle")){
                        std::cout << n << "\n";
                        auto const& triangle = n.find("triangle");
                        auto const& v1 = triangle->find("v1");
                        auto const& v2 = triangle->find("v2");
                        auto const& v3 = triangle->find("v3");
                        auto const& color = triangle->find("color");

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

                        index = 0;
                        for(auto const& c : *color){
                            buffer[index++] = c;
                        }

                        //TODO
                        // Make a shared_ptr<Triangle> and add it to scene vector

                    }
                }
            }
        }
        catch (...) {
            std::cerr << "INCORRECT FORMATTING OR MISSING ENTRIES IN \"group\"\n";
            exit(1);
        }
    }

}

/* init objects with scene data */
void init(Renderer& renderer, std::shared_ptr<Camera>& camera, Group& scene, Light &light, const std::string& path){
    std::ifstream f(RESOURCES_PATH + path + ".json");
    json data = json::parse(f);

    u32 index;
    f32 buffer[3];
    f32 color_buf[3];

    camera = collectCamera(data);
    collectBackground(data, renderer);
    collectScene(data, scene);
    light = collectLight(data);
}
