#include <iostream>

#include "Utilities/Macros.h"
#include "Utilities/Timer.h"
#include "Math/Matrix4.h"
#include "Math/Vector4.h"
#include "Math/Random.h"
#include "Beam/Ray.h"
#include "Beam/Hit.h"
#include "Camera/Camera.h"
#include "Camera/OrthographicCamera.h"
#include "Geometry/Object3D.h"
#include "Geometry/Sphere.h"
#include "Geometry/Group.h"
#include "Renderer/Image.h"
#include "Renderer/Renderer.h"

void init(Renderer& renderer, OrthographicCamera& camera, Group& scene, const std::string& path);

int main() {
    /* Start timer to measure program running time */
    Timer timer;

    /* JSON filenames are provided without the extension */
    std::string file1 = "scene1";
    std::string file2 = "scene2";

    /* Construct necessary objects */
    OrthographicCamera camera = OrthographicCamera(5, Vector4(0, 0, 10), Vector4(0, 0, -1), Vector4(0, 1, 0));
    Renderer renderer = Renderer(512, 512);
    Group scene = Group();

    /* init objects and render scenes */
    init(renderer, camera, scene, file1);
    renderer.Render(file1, camera, scene, 9, 11, false);
    renderer.Render(file1, camera, scene, 9, 11, true);

    init(renderer, camera, scene, file2);
    renderer.Render(file2, camera, scene, 8, 11.5, false);
    renderer.Render(file2, camera, scene, 8, 11.5, true);

    return 0;
}

/* init objects with scene data */
void init(Renderer& renderer, OrthographicCamera& camera, Group& scene, const std::string& path){
    std::ifstream f(RESOURCES_PATH + path + ".json");
    json data = json::parse(f);

    auto orthocamera = data.find("orthocamera");
    auto background = data.find("background");
    auto group = data.find("group");
    u32 index;
    f32 buffer[3];
    u8 color_buf[3];

    {
        index = 0;
        for(const auto& n : *background->find("color")){
            //std::cout << n << "\n";
            renderer.m_background_color[index++] = n;
        }
    }

    {
        index = 0;
        for(const auto& component : *orthocamera->find("center")){
            //std::cout << component << "\n";
            buffer[index++] = component;
        }
        camera.m_center = Vector4(buffer[0], buffer[1], buffer[2], 1.0);
    }

    {
        index = 0;
        for(const auto& component : *orthocamera->find("direction")){
            //std::cout << component << "\n";
            buffer[index++] = component;
        }
        camera.m_direction = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
    }

    {
        index = 0;
        for(const auto& component : *orthocamera->find("up")){
            //std::cout << component << "\n";
            buffer[index++] = component;
        }
        camera.m_up = Vector4(buffer[0], buffer[1], buffer[2], 0.0);
    }

    {
        auto s = orthocamera->find("size")->dump();
        camera.m_size = stoi(s);
        //std::cout << camera.m_size;
    }
    {
        scene.objects.clear();
        for (const auto& n : *group){
            if(n.find("sphere") != n.end()){
                //std::cout << n << "\n";
                auto const& sphere = n.find("sphere");
                auto const& center = sphere->find("center");
                auto const& radius = sphere->find("radius");
                auto const& color = sphere->find("color");

                index = 0;
                for(auto const& p : *center){
                    buffer[index++] = p;
                }

                auto r = radius->dump();
                std::shared_ptr<Sphere> sp0 = std::make_shared<Sphere>(Sphere(stof(r), Vector4(buffer[0], buffer[1], buffer[2], 1.0)));

                index = 0;
                for(auto const& c : *color){
                    color_buf[index++] = c;
                }

                memcpy(sp0->m_color, color_buf, sizeof(color_buf));
                scene.objects.push_back(sp0);
            }
        }
    }

}
