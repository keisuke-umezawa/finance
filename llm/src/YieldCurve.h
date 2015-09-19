#ifndef YIELDCURVE_H_INCLUDED
#define YIELDCURVE_H_INCLUDED

#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include "fwd.h"

namespace lmm {

    class IYieldCurve {
    public:
        virtual ~IYieldCurve() {}

        boost::shared_ptr<IYieldCurve> clone() const
        {
            return boost::shared_ptr<IYieldCurve>(doClone());
        }

        virtual const double discountFactor(
            const date_t& start, const date_t& end) const = 0;

    private:
        virtual IYieldCurve* doClone() const = 0;
    };

    class ConstantRateYieldCurve : public IYieldCurve {
    public:
        ConstantRateYieldCurve(const double rate,
            const boost::function<double(date_t, date_t)> dayCountFraction)
        : _rate(rate), _dayCountFraction(dayCountFraction)
        {
        }

        virtual ~ConstantRateYieldCurve() {}

        virtual const double discountFactor(
            const date_t& start, const date_t& end) const
        {
            return std::exp(-_rate * _dayCountFraction(start, end));
        }

    private:
        virtual ConstantRateYieldCurve* doClone() const
        {
            return new ConstantRateYieldCurve(*this);
        }

    private:
        const double _rate;
        const boost::function<double(date_t, date_t)> _dayCountFraction;
    };
        
} // namespace lmm {

#endif // YIELDCURVE_H_INCLUDED
