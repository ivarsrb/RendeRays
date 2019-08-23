#include "application.h"
#include "render_target.h"
#include "camera.h"
#include "sphere.h"

#define PIXEL_WIDTH 400
#define PIXEL_HEIGHT 300

Application::Application() : 
    render_buffer_(PIXEL_WIDTH, PIXEL_HEIGHT,t::kColorGray) {
    // Describe a scene
    scene_.AddCanera(Camera(t::Vec3(1.0, 0.0, -2.0), 0.0, 60.0, PIXEL_WIDTH, PIXEL_HEIGHT));
    scene_.AddRenderable(Sphere(t::Vec3(0.0, 0.0, -5.0), 0.5f, t::kColorRed));
}

// Execution of a rendering and storage process, could be looped 
void Application::Run() {
    tracer_.Render(scene_, render_buffer_);
    // Medium to whitch final render is stored
    RenderTarget render_target("output\\output_1.ppm");
    render_buffer_.PresentTo(render_target);
    render_target.Show();
}
