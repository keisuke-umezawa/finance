#ifndef CLOSEDFORMPRICER_H_INCLUDED
#define CLOSEDFORMPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"
#include "ChainOfPricer.h"
#include "YieldCurve.h"
#include "ChainOfPricerNode.h"

namespace design_pattern {

    class ClosedFormPricer : public ChainOfPricer {
    public:
        ClosedFormPricer(const YieldCurve& yieldCurve,
            const boost::shared_ptr<const ChainOfPricer>& successor);

        virtual double evaluate(const IContract& contract) const;
    private:
        const ChainOfPricerNode _successor;
        const boost::shared_ptr<const YieldCurve> _yieldCurve;
    };
} // namespace design_pattern {

#endif // CLOSEDFORMPRICER_H_INCLUDED