#pragma once

#include <memory>

#include "tokens.hpp"

namespace grammar {

class rule_base;
using rule = std::shared_ptr<rule_base>;
using rules = std::vector<rule>;

/*************/
/* rule_base */
/*************/

class rule_base {
public:
    virtual ~rule_base() = default;

    virtual const char* type_id() const = 0;

    template <class Derived> Derived& is() {
        return type_id() == Derived::static_type_id();
    }

    template <class Derived> Derived& as() {
        return static_cast<Derived&>(*this);
    }
};

/*******/
/* cmd */
/*******/

class cmd : public rule_base {
public:
    static constexpr const char* static_type_id() { return "cmd"; }

    static rule build(const token& name) {
        struct builder : public cmd {
            builder(const token& name) : cmd(name){};
        };

        return std::make_shared<builder>(name);
    }

    constexpr void add_arg(const token& arg) { args_.emplace_back(arg); }

    constexpr void add_cmd(const rule& cmd) { pipeline_.emplace_back(cmd); }

    constexpr void set_background(bool val = true) { this->background_ = val; }

    const std::string& get_name() const { return name_->as<word>().get_str(); }

    std::vector<std::string> get_args() const {
        std::vector<std::string> args;
        for (const auto& arg : args_) {
            args.emplace_back(arg->as<word>().get_str());
        }

        return args;
    }

    constexpr const char* type_id() const override { return static_type_id(); }

protected:
    cmd(const token& name) : name_(name) {}

private:
    token name_;
    tokens args_;
    rules pipeline_;
    bool background_ = false;
};

} // namespace grammar
