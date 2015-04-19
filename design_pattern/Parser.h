#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <boost/tokenizer.hpp>
#include "Fwd.h"
#include "IrDataBuilder.h"

namespace design_pattern {
    // Director
    class IrDataParser {
    public:
        IrDataParser(IrDataBuilder& builder)
        : _builder(builder)
        {
        }

        void parse(const std::string& dirPath)
        {
            std::ifstream ifst(dirPath.c_str());
            std::string str;

            while(std::getline(ifst, str)) {
                parseIrData(str);
            }
        }

    private:
        void parseIrData(const std::string& input)
        {
            typedef boost::char_separator<char> char_separator;
            typedef boost::tokenizer<char_separator> tokenizer;

            char_separator sep(",", "", boost::keep_empty_tokens);
            tokenizer token(input, sep);

            std::vector<std::string> dataStrings;
            for (tokenizer::iterator it = token.begin();
                    it != token.end(); ++it) {
                dataStrings.push_back(*it);
            }

            if (dataStrings[0] == "DEPO") {
                _builder.buildDepositeRateData(dataStrings);
            }
            else if (dataStrings[0] == "FRA") {
                _builder.buildForwardRateAgreementData(dataStrings);
            }
            else {
                _builder.buildSwapRateData(dataStrings);
            }
        }

        IrDataBuilder& _builder;
    };
} // namespace design_pattern

#endif // PARSER_H_INCLUDED