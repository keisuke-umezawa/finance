#ifndef INODE_H_INCLUDED
#define INODE_H_INCLUDED

#include "Context.h"

namespace design_pattern {
    class INode {
    public:
        virtual ~INode() {}
        virtual void parse(Context context) = 0;
        virtual double getResult() const = 0;
    };

}  // namespace design_pattern

#endif // INODE_H_INCLUDED
