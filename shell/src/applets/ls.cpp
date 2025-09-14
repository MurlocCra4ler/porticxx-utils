#include <algorithm>
#include <filesystem>
#include <iostream>

#include "applets.hpp"

namespace applet {

class ls : public applet_base {
protected:
    int do_run(const std::vector<std::string>& args) override {
        std::string path = ".";

        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            files.push_back(entry.path().filename());
        }

        std::sort(files.begin(), files.end());
        for (const auto& file : files) {
            std::cout << file << std::endl;
        }

        return 0;
    }
};

applet ls = std::make_shared<class ls>();

} // namespace applet
