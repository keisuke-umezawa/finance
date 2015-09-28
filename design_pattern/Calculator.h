#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Context.h"
#include "INode.h"
#include "ExpressionNode.h"

namespace design_pattern {
    class Calculator {
    public:
        Calculator()
        : _node(boost::make_shared<ExpressionNode>())
        {
        }

        double calc(const std::string& expression)
        {
            Context context(expression);
            _node->parse(context);
            return _node->getResult();
        }

    private:
        const boost::shared_ptr<INode> _node;
    };
} // namespace design_pattern {

#endif // CALCULATOR_H_INCLUDED
