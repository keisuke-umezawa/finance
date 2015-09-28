#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "LeastSquareMonteCarloPricer.h"
#include "YieldCurve.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {
    LeastSquareMonteCarloPricer::LeastSquareMonteCarloPricer(
        const YieldCurve& yieldCurve, 
        const SabrModelParameter& parameter,
        const boost::shared_ptr<const ChainOfPricer>& successor)
    : _successor(successor),
        _yieldCurve(yieldCurve.clone()), _parameter(parameter)
    {
    }
    double LeastSquareMonteCarloPricer::evaluate(const IContract& contract) const
    {
        if (contract.exerciseType() == American
                || contract.exerciseType() == Bermudan) {
            std::cout << " least square mc pricer " << std::endl;
            return 10.0;
        }
        return _successor.next(contract);
    }
} // namespace design_pattern {
