#pragma once

#include <iostream>
#include <vector>

#include "rules.hpp"
#include "tokens.hpp"

class parser {
public:
    static constexpr grammar::tokens tokenize(const std::string& line) {
        std::vector<grammar::token> tokens;

        size_t pos = 0;
        while (pos != line.size()) {
            skip_ws(line, pos);

            std::size_t count;
            if ((count = grammar::word::match(line, pos)) > 0) {
                tokens.emplace_back(
                    grammar::word::build(line.substr(pos, count)));
                pos += count;
                continue;
            }

            std::cerr << "parsing error: malformed input" << std::endl;
            return {};
        }

        return tokens;
    }

    static constexpr grammar::rule parse(const grammar::tokens& tokens) {
        if (tokens.empty())
            return {};

        size_t pos = 0;
        return parse_cmd(tokens, pos);
    }

private:
    static constexpr grammar::rule parse_cmd(const grammar::tokens& tokens,
                                             size_t& pos) {
        if (tokens.empty()) {
            return {};
        } else if (!tokens[pos]->is<grammar::word>()) {
            std::cerr << "parsing error: malformed input" << std::endl;
            return {};
        }

        grammar::rule cmd = grammar::cmd::build(tokens[pos++]);

        for (; pos < tokens.size(); pos++) {
            if (!tokens[pos]->is<grammar::word>()) {
                break;
            }

            cmd->as<grammar::cmd>().add_arg(tokens[pos]);
        }

        return cmd;
    }

    static constexpr void skip_ws(const std::string& str, std::size_t& pos) {
        for (; pos < str.size() &&
               std::isspace(static_cast<unsigned char>(str[pos]));
             ++pos)
            ;
    }
};