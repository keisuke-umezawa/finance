#ifndef EXPRESSIONNODE_H_INCLUDED
#define EXPRESSIONNODE_H_INCLUDED

#include "Context.h"
#include "INode.h"
#include "NumberNode.h"
#include "ExpressionNode.h"
#include "TermChain.h"

namespace design_pattern {

    // <expression> ::= <term> { + <term> | - <term> }*
    class ExpressionNode : public INode {
    public:
        virtual void parse(Context context);

        virtual double getResult() const;

    private:
        void addChain(const std::string& previousString, 
            const ExpressionTypeEnum currentExpression);

        std::vector<TermChain> _termChains;
    };

}  // namespace design_pattern

#endif // EXPRESSIONNODE_H_INCLUDED
