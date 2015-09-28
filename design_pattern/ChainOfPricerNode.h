#ifndef CHAINOFPRICERNODE_H_INCLUDED
#define CHAINOFPRICERNODE_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"

namespace design_pattern {
    class ChainOfPricer;

    class ChainOfPricerNode {
    public:
        ChainOfPricerNode(const boost::shared_ptr<const ChainOfPricer>& successor);

        double evaluate(const IContract& contract) const;
        double next(const IContract& contract) const;
    private:
        const boost::shared_ptr<const ChainOfPricer> _successor;
    };
} // namespace design_pattern {

#endif // CHAINOFPRICERNODE_H_INCLUDED