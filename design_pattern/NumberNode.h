#ifndef NUMBERNODE_H_INCLUDED
#define NUMBERNODE_H_INCLUDED

#include "Context.h"
#include "INode.h"

namespace design_pattern {
    class NumberNode : public INode {
    public:
        virtual void parse(Context context)
        {
            Context copy(context);
            _value = copy.currentTokenAsDouble();
            copy.next();
        }

        virtual double getResult() const
        {
            return _value;
        }

    private:
        double _value;
    };

}  // namespace design_pattern

#endif // NUMBERNODE_H_INCLUDED
