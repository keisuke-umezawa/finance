#ifndef FACTORCHAIN_H_INCLUDED
#define FACTORCHAIN_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "INode.h"

namespace design_pattern {
    enum TermTypeEnum {
        FactorTerm = 0,
        MultiplyTerm,
        DivideTerm
    };

    class FactorChain {
    public:
        FactorChain(TermTypeEnum termType, 
            const boost::shared_ptr<const INode>& node)
        : _termType(termType), _node(node)
        {
        }

        TermTypeEnum termType() const
        {
            return _termType;
        }
        double getResult() const
        {
            return _node->getResult();
        }
    private:
        TermTypeEnum _termType;
        boost::shared_ptr<const INode> _node;
    };

}  // namespace design_pattern

#endif // FACTORCHAIN_H_INCLUDED
