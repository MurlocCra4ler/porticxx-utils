#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace applet {

class applet_base;
using applet = std::shared_ptr<applet_base>;

class applet_base {
public:
    virtual ~applet_base() = default;

    int run(const std::vector<std::string>& args) { return do_run(args); }

protected:
    virtual int do_run(const std::vector<std::string>& args) = 0;
};

const std::unordered_map<std::string, applet>& get_builtins();

} // namespace applet
