#ifndef FXFDMPRICER_H_INCLUDED
#define FXFDMPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ChainOfPricer.h"
#include "YieldCurve.h"
#include "SabrModelParameter.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {
    class FxFdmPricer : public ChainOfPricer {
    public:
        FxFdmPricer(const YieldCurve& yieldCurve, 
            const SabrModelParameter& parameter,
            const boost::shared_ptr<const ChainOfPricer>& successor)
        : _successor(successor), 
            _yieldCurve(yieldCurve.clone()), _parameter(parameter)
        {
        }
        virtual double evaluate(const IContract& contract) const
        {
            if (contract.underlyingType() == Fx) {
                std::cout << " fdm pricer " << std::endl;
                return 4.0;
            }
            return _successor.next(contract);
        }
    private:
        const ChainOfPricerNode _successor;
        const boost::shared_ptr<const YieldCurve> _yieldCurve;
        const SabrModelParameter _parameter;
    };
} // namespace design_pattern {

#endif // FXFDMPRICER_H_INCLUDED