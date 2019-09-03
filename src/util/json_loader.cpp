#include "json_loader.h"
#include <fstream>
#include <stdexcept>
#include "log.h"

namespace util {
JSONLoader::JSONLoader(const std::string& file_name) : 
    parsed_data_(Init(file_name)) {
    Log::Info("Parsing of '", file_name, "' complete");
}

const nlohmann::json JSONLoader::Get() const {
    return parsed_data_;
}

// NOTE: string_view could have been passed if: ifstream accepted it (this can be solved through data() f-tion)
//       but the main problem is lack of + operator for string view to use it in exception description, 
//       maybe this will change in the future.
nlohmann::json JSONLoader::Init(const std::string& file_name) const {
    Log::Info("Parsing json file '", file_name, "' ...");
    std::ifstream file_stream(file_name, std::ifstream::in);
    if (file_stream.fail()) {
        throw std::runtime_error("Error opening file '" + file_name + "'");
    }
    // Throws if error while parsing
    return nlohmann::json::parse(file_stream);
}
}; // util