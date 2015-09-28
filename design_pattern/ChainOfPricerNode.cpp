#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ChainOfPricerNode.h"
#include "ChainOfPricer.h"


namespace design_pattern {

    ChainOfPricerNode::ChainOfPricerNode(
        const boost::shared_ptr<const ChainOfPricer>& successor)
    : _successor(successor)
    {
    }
    double ChainOfPricerNode::evaluate(const IContract& contract) const
    {
        return _successor->evaluate(contract);
    }

    double ChainOfPricerNode::next(const IContract& contract) const
    {
        if (_successor) {
            return _successor->evaluate(contract);
        }
        assert(!"This contract is not evaluated");
        return 0.0;
    }
} // namespace design_pattern {