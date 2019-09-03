#include "cmd_line_parser.h"
#include <algorithm>
#include "log.h"

namespace util {
CmdLineParser::CmdLineParser(uint32_t argc,  char* argv[]) :
    tokens_(GetTokens(argc, argv)) {
    //Log::Info("Command line parsing complete. ", tokens_.size()," tokens found");
}

std::string CmdLineParser::GetOption(std::string_view option) const {
    TokenVector::const_iterator itr;
    itr = std::find(tokens_.begin(), tokens_.end(), option);
    // If option token exists and that tokken that follows after option also exists
    if (itr != this->tokens_.end() && ++itr != this->tokens_.end()) {
        // Return the one that follows an option 
        return *itr;
    }
    return std::string("");
}

bool CmdLineParser::OptionExists(std::string_view token) const {
    return std::find(tokens_.begin(), tokens_.end(), token) != tokens_.end();
}

CmdLineParser::TokenVector CmdLineParser::GetTokens(uint32_t argc, char* argv[]) const {
    TokenVector tokens;
    // Starting from 1 because first one is exe file name
    for (uint32_t i = 1; i < argc; ++i) {
        tokens.push_back(std::string(argv[i]));
    }
    return tokens;
}
}; // util