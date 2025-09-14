#include <filesystem>

#include "applets.hpp"

namespace applet {

class cd : public applet_base {
protected:
    int do_run(const std::vector<std::string>& args) override {
        if (args.empty()) {
            std::filesystem::path cwd = std::filesystem::current_path();
            std::filesystem::current_path(cwd.root_directory());
        } else {
            std::filesystem::current_path(args[0]);
        }

        return 0;
    }
};

applet cd = std::make_shared<class cd>();

} // namespace applet
