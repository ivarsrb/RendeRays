#include "application.h"
#include "render_target.h"
#include "util/timing.h"
#include "util/log.h"

Application::Application() : 
    scene_("scene.json"),
    render_buffer_(scene_.GetOutputSize(), t::kColorWhite) {
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
