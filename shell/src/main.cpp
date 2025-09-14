#include <filesystem>
#include <iostream>

#include "applets/applets.hpp"
#include "parser.hpp"

/* cmd [arg]* [| cmd [arg]*]* [[> filename] [< filename] [>& filename] [>>
 * filename] [>>& filename]]* [&] */

int main() {
    const auto& builtins = applet::get_builtins();

    std::string line_buffer;
    int last_exit_code = 0;

    while (true) {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cout << cwd << ">";
        std::cout.flush();

        std::getline(std::cin, line_buffer);
        const auto tokens = parser::tokenize(line_buffer);

        const auto ast = parser::parse(tokens);
        if (!ast) {
            continue;
        }

        const auto& cmd = ast->as<grammar::cmd>();
        if (cmd.get_name() == "?") {
            std::cout << "last exit code: " << last_exit_code << std::endl;
            continue;
        }

        auto it = builtins.find(cmd.get_name());
        if (it != builtins.end()) {
            // shell builtin
            const auto& applet = it->second;
            last_exit_code = applet->run(cmd.get_args());
            continue;
        }

        const std::vector<std::string> args = cmd.get_args();
        std::vector<const char*> argv{cmd.get_name().c_str()};
        for (const auto& arg : args) {
            argv.push_back(arg.c_str());
        }
        argv.push_back(nullptr);

        last_exit_code =
            std::arch::current_arch::exec(cmd.get_name().c_str(), argv.data());
    }
}
