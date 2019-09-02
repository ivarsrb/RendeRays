#include "application.h"
#include "render_target.h"
#include "camera.h"
#include "light/ambient.h"
#include "light/directional.h"
#include "renderable/sphere.h"
#include "renderable/aa_box.h"
#include "util/timing.h"
#include "util/log.h"


#define PIXEL_WIDTH 800
#define PIXEL_HEIGHT 600

Application::Application() : 
    scene_("Test scene", t::kColorGray),
    render_buffer_(t::Size16{ PIXEL_WIDTH, PIXEL_HEIGHT }, t::kColorWhite) {
    // Describe a scene
    scene_.AddCanera(Camera(t::Vec3(0.0, 0.0, 5.0), 0.0, 60.0, t::Size16{ PIXEL_WIDTH , PIXEL_HEIGHT }));
    scene_.AddCanera(Camera(t::Vec3(5.0, 0.0, 0.0), 90.0, 60.0, t::Size16{ PIXEL_WIDTH , PIXEL_HEIGHT }));
    scene_.AddCanera(Camera(t::Vec3(0.0, 0.0, -5.0), 180.0, 60.0, t::Size16{ PIXEL_WIDTH , PIXEL_HEIGHT }));
    scene_.AddCanera(Camera(t::Vec3(-5.0, 0.0, 0.0), 270.0, 60.0, t::Size16{ PIXEL_WIDTH , PIXEL_HEIGHT }));

    //scene_.SetLight(std::make_unique<light::Ambient>(t::Vec3(1.0, 1.0, 1.0)));
    scene_.SetLight(std::make_unique<light::Directional>(t::Vec3(1.5, -1.0, -1.0), t::Vec3(0.2, 0.2, 0.2), t::Vec3(1.0, 1.0, 1.0)));

    scene_.AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(-1.0, 0.0, -1.0), 0.5f, t::kColorRed));
    //scene_.AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(0.0, 0.0, -5.0), 1.5f, t::kColorRed));
    //scene_.AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(4.5, 0.0, -7.0), 0.5f, t::kColorBlue));
    scene_.AddRenderable(std::make_unique<renderable::AABox>(t::Vec3(2.0, 1.5, 0.0), 1.0f, t::kColorGreen));
    scene_.AddRenderable(std::make_unique<renderable::AABox>(t::Vec3(3.0, 0.0, -5.0), 0.5f, t::kColorBlue));
}

// Execution of a rendering and storage process
// From each vantage point one-by-one.
void Application::Run() {
    for (size_t camera_id = 0; camera_id < scene_.GetCameras().size(); ++camera_id) {
        render_buffer_.Clear(t::kColorWhite);
        util::Log::Info("Rendering the scene '" + scene_.GetName() + "'. Render nr. " + 
            std::to_string(camera_id)  +  "...");
        util::Timing timer;
        tracer_.Render(scene_, scene_.GetCameras().at(camera_id), render_buffer_);
        timer.SetTime2(true);
        util::Log::Info("Presenting scene '" + scene_.GetName() + "' to render target...");
        timer.SetTime1();
        // Medium to whitch final render is stored
        RenderTarget render_target(scene_.GetName(), static_cast<t::U16>(camera_id));
        render_buffer_.PresentTo(render_target);
        timer.SetTime2(true);
        render_target.Show();
    }
}
