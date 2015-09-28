#ifndef FACTORNODE_H_INCLUDED
#define FACTORNODE_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "Context.h"
#include "INode.h"

namespace design_pattern {
    // <factor> ::= <literal> | ( <expression> )
    class FactorNode : public INode {
    public:
        virtual void parse(Context context);

        double getResult() const;
    private:
        void processInBracket(Context context);

        boost::shared_ptr<INode> _node;
    };

}  // namespace design_pattern

#endif // FACTORNODE_H_INCLUDED
