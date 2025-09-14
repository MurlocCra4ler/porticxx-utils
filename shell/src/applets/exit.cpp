#include <cstdlib>

#include "applets.hpp"

namespace applet {

class exit : public applet_base {
protected:
    int do_run(const std::vector<std::string>& args) override { std::exit(0); }
};

applet exit = std::make_shared<class exit>();

} // namespace applet
