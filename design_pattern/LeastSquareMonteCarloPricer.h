#ifndef LEASTSQUAREMONTECARLOPRICER_H_INCLUDED
#define LEASTSQUAREMONTECARLOPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ChainOfPricer.h"
#include "YieldCurve.h"
#include "SabrModelParameter.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {
    class LeastSquareMonteCarloPricer : public ChainOfPricer {
    public:
        LeastSquareMonteCarloPricer(const YieldCurve& yieldCurve, 
            const SabrModelParameter& parameter,
            const boost::shared_ptr<const ChainOfPricer>& successor);
        virtual double evaluate(const IContract& contract) const;
    private:
        const ChainOfPricerNode _successor;
        const boost::shared_ptr<const YieldCurve> _yieldCurve;
        const SabrModelParameter _parameter;
    };
} // namespace design_pattern {

#endif // LEASTSQUAREMONTECARLOPRICER_H_INCLUDED