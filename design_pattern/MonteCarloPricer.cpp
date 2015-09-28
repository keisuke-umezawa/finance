#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "MonteCarloPricer.h"
#include "YieldCurve.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {
    MonteCarloPricer::MonteCarloPricer(const YieldCurve& yieldCurve, 
        const SabrModelParameter& parameter)
    : _successor(boost::shared_ptr<ChainOfPricer>()),
        _yieldCurve(yieldCurve.clone()), _parameter(parameter)
    {
    }
    double MonteCarloPricer::evaluate(const IContract& contract) const
    {
        std::cout << " monte carlo pricer " << std::endl;
        return 4.0;
    }
} // namespace design_pattern {
