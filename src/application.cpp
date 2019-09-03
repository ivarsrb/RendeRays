#include "application.h"
#include "render_target.h"
#include "util/timing.h"
#include "util/log.h"
#include "util/util.h"

Application::Application(int argc, char* argv[]) :
    cmd_line_parser_(argc, argv),
    scene_(GetSceneFileName(cmd_line_parser_.GetOption("-f"))),
    render_buffer_(scene_.GetOutputSize(), t::kColorWhite) {
}

// Execution of a rendering and storage process
// From each vantage point one-by-one.
void Application::Run() {
    util::Log::Info("Rendering the scene '" + scene_.GetName() + "'.");
    util::Timing timer;
    for (size_t camera_id = 0; camera_id < scene_.GetCameras().size(); ++camera_id) {
        render_buffer_.Clear(t::kColorWhite);
        util::Log::Info("Render for camera nr. " + std::to_string(camera_id)  +  "...");
        timer.SetTime1();
        tracer_.Render(scene_, scene_.GetCameras().at(camera_id), render_buffer_);
        util::Log::Info("... " + std::to_string(timer.SetTime2(false)), " ms");
        util::Log::Info("Presenting render for camera nr. " + std::to_string(camera_id) + " to render target...");
        timer.SetTime1();
        // Medium to whitch final render is stored
        RenderTarget render_target(scene_.GetName(), static_cast<t::U16>(camera_id));
        render_buffer_.PresentTo(render_target);
        util::Log::Info("... " + std::to_string(timer.SetTime2(false)), " ms");
        // If showing is enabled
        if (cmd_line_parser_.OptionExists("-s")) {
            // Blocking call
            render_target.Show();
        }
    }
}

// File is looked for in subfolder that is relative to executable
std::string Application::GetSceneFileName(const std::string& file_name) const {
    const std::string sub_folder = "scenes/";
    return std::string(sub_folder + util::StripIlligallChars(file_name));
}
