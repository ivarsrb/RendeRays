#include "application.h"
#include "render_target.h"
#include "camera.h"
#include "renderable/sphere.h"
#include "renderable/aa_box.h"
#include "util/timing.h"
#include "util/log.h"

#define PIXEL_WIDTH 800
#define PIXEL_HEIGHT 600

Application::Application() : 
    render_buffer_(t::Size16{ PIXEL_WIDTH, PIXEL_HEIGHT }, t::kColorGray) {
    // Describe a scene
    scene_.AddCanera(Camera(t::Vec3(0.0, 0.0, 1.0), 0.0, 60.0, t::Size16{ PIXEL_WIDTH , PIXEL_HEIGHT }));
    //scene_.AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(0.0, 0.0, -5.0), 1.5f, t::kColorRed));
    //scene_.AddRenderable(std::make_unique<renderable::Sphere>(t::Vec3(0.5, 0.0, -7.0), 0.5f, t::kColorBlue));
    scene_.AddRenderable(std::make_unique<renderable::AABox>(t::Vec3(0.0, 0.0, -3.0), 0.5f, t::kColorGreen));
    scene_.AddRenderable(std::make_unique<renderable::AABox>(t::Vec3(3.0, 0.0, -5.0), 0.5f, t::kColorRed));
}

// Execution of a rendering and storage process, could be looped 
void Application::Run() {
    util::Log::Info("Rendering the scene...");
    util::Timing timer;
    tracer_.Render(scene_, render_buffer_);
    timer.SetTime2(true);
    util::Log::Info("Presenting to render target...");
    timer.SetTime1();
    // Medium to whitch final render is stored
    RenderTarget render_target("output\\output_1.ppm");
    render_buffer_.PresentTo(render_target);
    timer.SetTime2(true);
    render_target.Show();
}
