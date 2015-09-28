
#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

namespace design_pattern {
    class Context {
    private:
        typedef boost::char_separator<char> char_separator_type;
        typedef boost::tokenizer<char_separator_type> tokenizer_type;

    public:
        Context(const std::string& string);

        void next();

        std::string current() const;

        bool isEmpty() const;
        bool isLeftBracket() const;
        bool isRightBracket() const;
        bool isPlus() const;
        bool isMinus() const;
        bool isMultiply() const;
        bool isDivide() const;

        double currentTokenAsDouble() const;

    private:
        tokenizer_type _tokenizer;
        tokenizer_type::iterator _iterator;
    };
}  // namespace design_pattern

#endif // CONTEXT_H_INCLUDED
