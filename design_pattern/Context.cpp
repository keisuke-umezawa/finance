#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "Context.h"

namespace design_pattern {
    Context::Context(const std::string& string)
        : _tokenizer(string),
        _iterator(_tokenizer.begin())
    {
    }

    void Context::next()
    {
        if (_iterator == _tokenizer.end()) {
            return;
        }
        ++_iterator;
    }

    std::string Context::current() const
    {
        if (_iterator == _tokenizer.end()) {
            return "";
        }
        return *_iterator;
    }

    bool Context::isEmpty() const
    {
        return "" == this->current();
    }

    bool Context::isLeftBracket() const
    {
        return "(" == this->current();
    }

    bool Context::isRightBracket() const
    {
        return ")" == this->current();
    }

    bool Context::isPlus() const
    {
        return "+" == this->current();
    }

    bool Context::isMinus() const
    {
        return "-" == this->current();
    }

    bool Context::isMultiply() const
    {
        return "*" == this->current();
    }

    bool Context::isDivide() const
    {
        return "/" == this->current();
    }

    double Context::currentTokenAsDouble() const
    {
        return boost::lexical_cast<double>(*_iterator);
    }
}  // namespace design_pattern