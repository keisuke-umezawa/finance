#include "TermNode.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>
#include "Context.h"
#include "INode.h"
#include "FactorChain.h"
#include "FactorNode.h"

namespace design_pattern {

    void TermNode::parse(Context context)
    {
        std::string previousString("");
        TermTypeEnum currentTerm = FactorTerm;
        int bracketDepth = 0;
        for (; !context.isEmpty(); context.next()) {
            if (context.isLeftBracket()) {
                ++bracketDepth;
            }
            if (context.isRightBracket()) {
                --bracketDepth;
            }

            if (context.isMultiply() && 0 == bracketDepth) {
                this->addChain(previousString, currentTerm);
                previousString = "";
                currentTerm = MultiplyTerm;
            }
            else if (context.isDivide() && 0 == bracketDepth) {
                this->addChain(previousString, currentTerm);
                previousString = "";
                currentTerm = DivideTerm;
            }
            else {
                previousString += context.current() + " ";
            }
        }
        if (!previousString.empty()) {
            this->addChain(previousString, currentTerm);
        }
    }

    double TermNode::getResult() const
    {
        double result = 0.0;

        BOOST_FOREACH(const FactorChain& factor, _factorChains) {
            if (FactorTerm == factor.termType()) {
                result = factor.getResult();
            }
            if (MultiplyTerm == factor.termType()) {
                result *= factor.getResult();
            }
            if (DivideTerm == factor.termType()) {
                result /= factor.getResult();
            }
        }

        return result;
    }

    void TermNode::addChain(const std::string& previousString, 
        const TermTypeEnum currentTerm)
    {
        std::string copy = previousString;
        copy.erase(copy.size() - 1);
        Context previousContext(copy);

        boost::shared_ptr<INode> node = boost::make_shared<FactorNode>();
        node->parse(previousContext);
        _factorChains.push_back(FactorChain(currentTerm, node));
    }

}  // namespace design_pattern
