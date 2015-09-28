#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ClosedFormPricer.h"
#include "YieldCurve.h"
#include "ChainOfPricerNode.h"


namespace design_pattern {
    ClosedFormPricer::ClosedFormPricer(const YieldCurve& yieldCurve,
        const boost::shared_ptr<const ChainOfPricer>& successor)
    : _successor(successor), _yieldCurve(yieldCurve.clone())
    {
    }
    double ClosedFormPricer::evaluate(const IContract& contract) const
    {
        if (contract.hasClosedFormula()) {
            std::cout << " closed form pricer " << std::endl;
            return 5.0;
        }
        return _successor.next(contract);
    }
} // namespace design_pattern {
