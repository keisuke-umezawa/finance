#ifndef TERMCHAIN_H_INCLUDED
#define TERMCHAIN_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "INode.h"

namespace design_pattern {
    enum ExpressionTypeEnum {
        TermExpression = 0,
        AddExpression,
        SubtExpression
    };

    class TermChain {
    public:
        TermChain(ExpressionTypeEnum expressionType, 
            const boost::shared_ptr<const INode>& node)
        : _expressionType(expressionType), _node(node)
        {
        }

        ExpressionTypeEnum expressionType() const
        {
            return _expressionType;
        }
        double getResult() const
        {
            return _node->getResult();
        }
    private:
        ExpressionTypeEnum _expressionType;
        boost::shared_ptr<const INode> _node;
    };

}  // namespace design_pattern

#endif // TERMCHAIN_H_INCLUDED
