#include <filesystem>
#include <iostream>

/* cmd [arg]* [| cmd [arg]*]* [[> filename] [< filename] [>& filename] [>> filename] [>>& filename]]* [&] */

int main() {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string line_buffer;

    while (true) {
        std::cout << cwd << ">";
        std::cout.flush();

        std::getline(std::cin, line_buffer);
    }
}
