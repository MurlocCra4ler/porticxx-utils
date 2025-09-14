#pragma once

#include <vector>

#include "token.hpp"

/* cmd [arg]* [| cmd [arg]*]* [[> filename] [< filename] [>& filename] [>>
 * filename] [>>& filename]]* [&] */

class redirection {
private:
    token op;
    token filename;
};

class cmd {
private:
    token name;
    std::vector<token> args;
    std::vector<redirection> redirections;
    std::vector<cmd> pipeline;
    bool background = false;
};
