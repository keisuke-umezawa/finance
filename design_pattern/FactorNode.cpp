#include "FactorNode.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "Context.h"
#include "INode.h"
#include "NumberNode.h"
#include "ExpressionNode.h"

namespace design_pattern {
    void FactorNode::parse(Context context)
    {
        if (context.isLeftBracket()) {
            processInBracket(context);
        }
        else {
            _node = boost::make_shared<NumberNode>();
            _node->parse(context);
        }
    }

    double FactorNode::getResult() const
    {
        return _node->getResult();
    }

    void FactorNode::processInBracket(Context context)
    {
        std::string stringInBracket("");
        int bracketDepth = 0;
        context.next();
        for(; !context.isRightBracket() || bracketDepth > 0; context.next()) {
            if (context.isLeftBracket()) {
                ++bracketDepth;
            }
            else if (context.isRightBracket()) {
                --bracketDepth;
            }
            stringInBracket += context.current() + " ";
        }
        stringInBracket.erase(stringInBracket.size() - 1);
        Context contextInBracket(stringInBracket);
        _node = boost::make_shared<ExpressionNode>();
        _node->parse(contextInBracket);
    }

}  // namespace design_pattern
