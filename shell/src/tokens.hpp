#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

namespace grammar {

class token_base;
using token = std::shared_ptr<token_base>;
using tokens = std::vector<token>;

class token_base {
public:
    virtual ~token_base() = default;

    virtual const char* type_id() const = 0;

    template <class Derived> bool is() const {
        return type_id() == Derived::static_type_id();
    }

    template <class Derived> Derived& as() {
        return static_cast<Derived&>(*this);
    }
};

class token_semicolon : token_base {
public:
    static size_t match(const std::string& str, size_t start) {
        return (str[start] == ';') ? 1 : 0;
    };
};

/********/
/* word */
/********/

class word : public token_base {
public:
    static constexpr const char* static_type_id() { return "word"; }

    static token build(const std::string& str) {
        struct builder : public word {
            builder(const std::string& str) : word(str){};
        };

        return std::make_shared<builder>(str);
    }

    static constexpr size_t match(const std::string& str, size_t start) {
        // empty string
        if (start >= str.size())
            return 0;

        // quoted word
        if (str[start] == '"') {
            size_t i = start + 1;
            bool escaped = false;
            while (i < str.size()) {
                char c = str[i];
                if (escaped) {
                    // skip escaped quotes
                    escaped = false;
                } else if (c == '\\') {
                    escaped = true;
                } else if (c == '"') {
                    // endquotes found
                    return i + 1 - start;
                }
                ++i;
            }

            // no endquotes found -> malformed
            return 0;
        }

        // unquoted word
        size_t i = start;
        while (i < str.size()) {
            char c = str[i];
            if (std::isspace(static_cast<unsigned char>(c)) || c == '|' ||
                c == '&' || c == ';' || c == '<' || c == '>') {
                break;
            }
            ++i;
        }
        return i - start;
    }

    const char* type_id() const override { return static_type_id(); }

    const std::string& get_str() const { return word_; }

protected:
    word(const std::string& str)
        : word_(str[0] == '"' ? str.substr(1, str.size() - 2) : str) {}

private:
    std::string word_;
};

}; // namespace grammar
