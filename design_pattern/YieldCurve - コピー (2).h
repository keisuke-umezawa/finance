#ifndef YIELDCURVE_H_INCLUDED
#define YIELDCURVE_H_INCLUDED

#include "fwd.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace design_pattern {

    class YieldCurveDataSet;

    class YieldCurve {
    public:
        virtual ~YieldCurve() {}

        boost::shared_ptr<YieldCurve> clone() const
        {
            return boost::shared_ptr<YieldCurve>(doClone());
        }

        virtual const double discountFactor(const date_t& date) const = 0;

        virtual void setYieldCurveDataSet(const YieldCurveDataSet& dataset) = 0;

        virtual void build() = 0;
    
    private:
        virtual YieldCurve* doClone() const = 0;
    };

    class OisYieldCurve : public YieldCurve {
    public:
        virtual ~OisYieldCurve() {}

        virtual const double discountFactor(const date_t& date) const
        {
            return 0.0;
        }

        virtual void setYieldCurveDataSet(const YieldCurveDataSet& dataset)
        {
        }

        virtual void build()
        {
        }
    
    private:
        virtual OisYieldCurve* doClone() const
        {
            return new OisYieldCurve(*this);
        }
    };

    class LiborYieldCurve : public YieldCurve {
    public:
        virtual ~LiborYieldCurve() {}

        boost::shared_ptr<LiborYieldCurve> clone() const
        {
            return boost::shared_ptr<LiborYieldCurve>(doClone());
        }

        virtual const double discountFactor(const date_t& date) const
        {
            return 1.0;
        }

        virtual void setYieldCurveDataSet(const YieldCurveDataSet& dataset)
        {
        }

        virtual void build()
        {
        }
    
    private:
        virtual LiborYieldCurve* doClone() const
        {
            return new LiborYieldCurve(*this);
        }
    };
        
}

#endif // YIELDCURVE_H_INCLUDED