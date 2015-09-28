#ifndef CHAINFOFPRICERBUILDER_H_INCLUDED
#define CHAINFOFPRICERBUILDER_H_INCLUDED

#include "ClosedFormPricer.h"
#include "FxFdmPricer.h"
#include "MonteCarloPricer.h"
#include "LeastSquareMonteCarloPricer.h"

namespace design_pattern {
    inline
    boost::shared_ptr<ChainOfPricer> makeChainOfPricer(
        const YieldCurve& yieldCurve,
        const SabrModelParameter& fxParameter,
        const SabrModelParameter& interestRateParameter) 
    {
        const boost::shared_ptr<ChainOfPricer> pricer1
            = boost::make_shared<MonteCarloPricer>(
                yieldCurve, interestRateParameter);
        const boost::shared_ptr<ChainOfPricer> pricer2
            = boost::make_shared<LeastSquareMonteCarloPricer>(
                yieldCurve, interestRateParameter, pricer1);
        const boost::shared_ptr<ChainOfPricer> pricer3
            = boost::make_shared<FxFdmPricer>(
                yieldCurve, fxParameter, pricer2);
        return boost::make_shared<ClosedFormPricer>(yieldCurve, pricer3);
    }
} // namespace design_pattern {

#endif CHAINFOFPRICERBUILDER_H_INCLUDED