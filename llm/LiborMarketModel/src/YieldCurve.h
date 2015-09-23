#ifndef YIELDCURVE_H_INCLUDED
#define YIELDCURVE_H_INCLUDED

#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include "fwd.h"
#include "LinearInterpolant.h"

namespace lmm {

    class IYieldCurve {
    public:
        virtual ~IYieldCurve() {}

        boost::shared_ptr<IYieldCurve> clone() const
        {
            return boost::shared_ptr<IYieldCurve>(doClone());
        }

        virtual const double discountFactor(
            const date_t& start, const date_t& end) const
        {
            return doDiscountFactor(start, end);
        }
    private:
        virtual const double doDiscountFactor(
            const date_t& start, const date_t& end) const = 0;
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
    private:
        virtual const double doDiscountFactor(
            const date_t& start, const date_t& end) const
        {
            return std::exp(-_rate * _dayCountFraction(start, end));
        }
        virtual ConstantRateYieldCurve* doClone() const
        {
            return new ConstantRateYieldCurve(*this);
        }

    private:
        const double _rate;
        const boost::function<double(date_t, date_t)> _dayCountFraction;
    };
        
    class PiecewiseYieldCurve : public IYieldCurve {
    public:
        PiecewiseYieldCurve(const IInterpolant& interpolant)
        : _interpolant(interpolant.clone())
        {

        }
        PiecewiseYieldCurve(const PiecewiseYieldCurve& other)
        : _interpolant(other._interpolant->clone())
        {
        }
        virtual ~PiecewiseYieldCurve() {}

    private:
        virtual const double doDiscountFactor(
            const date_t& start, const date_t& end) const
        {
            return (*_interpolant)(end) / (*_interpolant)(start);
        }
        virtual PiecewiseYieldCurve* doClone() const
        {
            return new PiecewiseYieldCurve(*this);
        }
    private:
        const boost::shared_ptr<const IInterpolant> _interpolant;
    };

    template <typename Interpolant> inline
    boost::shared_ptr<IYieldCurve> makePiecewiseYieldCurve(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& discountFactors)
    {
        ublas::vector<date_t> copyDates(dates);
        copyDates.insert_element(0, today);
        ublas::vector<double> copyDfs(discountFactors);
        copyDfs.insert_element(0, 1.0);
        return boost::make_shared<PiecewiseYieldCurve>(
            Interpolant(copyDates, copyDfs));
    }

    const double forwardRate(const IYieldCurve& yieldCurve,
        const date_t& today, const date_t& start, const date_t& end);
} // namespace lmm {

#endif // YIELDCURVE_H_INCLUDED
