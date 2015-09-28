#include "ExpressionNode.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>
#include "Context.h"
#include "INode.h"
#include "TermNode.h"
#include "TermChain.h"

namespace design_pattern {

    void ExpressionNode::parse(Context context)
    {
        std::string previousString("");
        ExpressionTypeEnum currentExpression = TermExpression;
        int bracketDepth = 0;
        for (; !context.isEmpty(); context.next()) {
            if (context.isLeftBracket()) {
                ++bracketDepth;
            }
            if (context.isRightBracket()) {
                --bracketDepth;
            }

            if (context.isPlus() && 0 == bracketDepth) {
                this->addChain(previousString, currentExpression);
                previousString = "";
                currentExpression = AddExpression;
            }
            else if (context.isMinus() && 0 == bracketDepth) {
                this->addChain(previousString, currentExpression);
                previousString = "";
                currentExpression = SubtExpression;
            }
            else {
                previousString += context.current() + " ";
            }
        }
        if (!previousString.empty()) {
            this->addChain(previousString, currentExpression);
        }
    }

    double ExpressionNode::getResult() const
    {
        double result = 0.0;

        BOOST_FOREACH(const TermChain& term, _termChains) {
            if (TermExpression == term.expressionType()) {
                result = term.getResult();
            }
            else if (AddExpression == term.expressionType()) {
                result += term.getResult();
            }
            else if (SubtExpression == term.expressionType()) {
                result -= term.getResult();
            }
        }

        return result;
    }

    void ExpressionNode::addChain(const std::string& previousString, 
        const ExpressionTypeEnum currentExpression)
    {
        std::string copy = previousString;
        copy.erase(copy.size() - 1);
        Context previousContext(copy);

        boost::shared_ptr<INode> node = boost::make_shared<TermNode>();
        node->parse(previousContext);
        _termChains.push_back(TermChain(currentExpression, node));
    }

}  // namespace design_pattern
