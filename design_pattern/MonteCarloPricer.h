#ifndef MONTECARLOPRICER_H_INCLUDED
#define MONTECARLOPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ChainOfPricer.h"
#include "YieldCurve.h"
#include "SabrModelParameter.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {
    class MonteCarloPricer : public ChainOfPricer {
    public:
        MonteCarloPricer(const YieldCurve& yieldCurve, 
            const SabrModelParameter& parameter);
        virtual double evaluate(const IContract& contract) const;
    private:
        const ChainOfPricerNode _successor;
        const boost::shared_ptr<const YieldCurve> _yieldCurve;
        const SabrModelParameter _parameter;
    };
} // namespace design_pattern {

#endif // MONTECARLOPRICER_H_INCLUDED