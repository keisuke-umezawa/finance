#ifndef YIELDCURVE_H_INCLUDED
#define YIELDCURVE_H_INCLUDED

#include "Fwd.h"
#include "YieldCurve.h"
#include <boost/shared_ptr.hpp>

namespace design_pattern {

    class MarketDataSet;

    class SwapRateDecorator : public YieldCurve {
    public:
        SwapRateDecorator(boost::shared_ptr<YieldCurve> ptrYieldCurve)
        : _ptrYieldCurve(ptrYieldCurve)
        {
        }

        virtual ~YieldCurveDecorator() {}

        virtual const double discountFactor(const date_t& date) const
        {
            return _ptrYieldCurve->discountFactor(date);
        }

        virtual void setMarketDataSet(const MarketDataSet& dataset)
        {
            _ptrYieldCurve->setMarketDateSet(dateset);
        }

        virtual void build()
        {
            _ptrYieldCurve->build();
        }
    
    private:
        virtual SwapRateDecorator* doClone() const
        {
            return new SwapRateDecorator(*this);
        }

        boost::shared_ptr<YieldCurve> _ptrYieldCurve;
    };        
}

#endif // YIELDCURVE_H_INCLUDED