#pragma once

#include <cstddef>
#include <string>
#include <cctype>

class token_base;
using token = std::shared_ptr<token_base>;

class token_base {
public:
    virtual ~token_base() = default;

    virtual const char* type_id() const = 0;

    template<class Derived>
    Derived& is() {
        return type_id() == Derived::static_type_id();
    }

    template<class Derived>
    Derived& as() {
        return static_cast<Derived&>(*this);
    }
};

class token_semicolon : token_base {
public:
    static size_t match(const std::string& str, size_t start) {
        return (str[start] == ';') ? 1 : 0;
    };
};

class token_word : public token_base {
public:
    static const char* static_type_id() { return "word"; }

    static token build(const std::string& str, size_t& pos) {
        class builder : public token_word {
        public:
            builder(const std::string& str, size_t& pos) : token_word(str, pos) {};
        };

        return std::make_shared<builder>(str, pos);
    }

    static const char* name() {
        return "word";
    }

    static size_t match(const std::string& str, size_t start) {
        size_t i = start;
        while (i < str.size()) {
            char c = str[i];
            if (isspace(static_cast<unsigned char>(c)) ||
                c == '|' || c == '&' || c == ';' ||
                c == '<' || c == '>') {
                break;
            }
            ++i;
        }
        return i - start;
    }

    const char* type_id() const override { return static_type_id(); }

protected:
    token_word(const std::string& str, size_t& pos) : word_(str.data(), match(str, pos)) {
        pos += word_.length();
    }

private:
    std::string_view word_;
};
