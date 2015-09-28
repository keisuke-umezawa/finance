#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ContractDispatcher.h"
#include "YieldCurve.h"
#include "SabrModelParameter.h"
#include "ChainOfPricerBuilder.h"

int main() 
{
    // market data
    const boost::shared_ptr<const design_pattern::YieldCurve> yieldCurve
        = boost::make_shared<design_pattern::LiborYieldCurve>();
    const design_pattern::SabrModelParameter fxParameter;
    const design_pattern::SabrModelParameter interestRateParameter;

    // contract
    const design_pattern::Cap cap;
    const design_pattern::FxVanillaOption fxOption;
    const design_pattern::AmericanSwaption americanSwaption;

    // make chain of pricer
    const boost::shared_ptr<const design_pattern::ChainOfPricer> chain
        = design_pattern::makeChainOfPricer(*yieldCurve, fxParameter, 
            interestRateParameter);

    // pricing
    std::cout << chain->evaluate(cap) << std::endl;
    std::cout << chain->evaluate(fxOption) << std::endl;
    std::cout << chain->evaluate(americanSwaption) << std::endl;

    return 0;
}