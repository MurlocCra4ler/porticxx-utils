#include "applets.hpp"

namespace applet {

extern applet cd;
extern applet exit;
extern applet ls;

const std::unordered_map<std::string, applet>& get_builtins() {
    static const std::unordered_map<std::string, applet> builtins{
        {"cd", cd},
        {"exit", exit},
        {"ls", ls},
    };

    return builtins;
}

} // namespace applet
