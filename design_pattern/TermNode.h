#ifndef TERMNODE_H_INCLUDED
#define TERMNODE_H_INCLUDED


#include "Context.h"
#include "INode.h"
#include "FactorChain.h"

namespace design_pattern {

    // <term> ::= <factor> { * <factor> | / <factor> }*
    class TermNode : public INode {
    public:
        virtual void parse(Context context);

        virtual double getResult() const;

    private:
        void TermNode::addChain(const std::string& previousString, 
            const TermTypeEnum currentTerm);

        std::vector<FactorChain> _factorChains;
    };

}  // namespace design_pattern

#endif // TERMNODE_H_INCLUDED
