#ifndef SWAPRATECALCULATOR_H_INCLUDED
#define SWAPRATECALCULATOR_H_INCLUDED

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"
#include "YieldCurve.h"
#include "Tenor.h"
#include "DayCountFraction.h"

namespace lmm {
    class SwapRateCalculator {
    public:
        SwapRateCalculator(
            const IYieldCurve& yieldCurve, const date_t& start,
            const ublas::vector<date_t>& dates)
        : _interpolant()
        {
            ublas::vector<double> rates(dates.size(), 0.0);
            const double firstDiscountFactor
                = yieldCurve.discountFactor(start, dates(0));
            double sum = 0.0;
            for (std::size_t i = 1; i < rates.size(); ++i) {
                const double df
                    = yieldCurve.discountFactor(start, dates(i));
                sum += df * dayCountAct360(dates(i - 1), dates(i));
                rates(i) 
                    = (firstDiscountFactor 
                        - yieldCurve.discountFactor(start, dates(i)))
                        / sum;
            }
            _interpolant = boost::make_shared<LinearInterpolant>(
                dates, rates);
        }
        const double get(const date_t& key) const
        {
            return (*_interpolant)(key);
        }

    private:
        boost::shared_ptr<LinearInterpolant> _interpolant;
    };

}  // namespace llm

#endif // SWAPRATECALCULATOR_H_INCLUDED
