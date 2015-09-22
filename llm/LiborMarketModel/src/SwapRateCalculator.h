#ifndef SWAPRATECALCULATOR_H_INCLUDED
#define SWAPRATECALCULATOR_H_INCLUDED

#include <algorithm>
#include "fwd.h"
#include "YieldCurve.h"
#include "Tenor.h"
#include "DayCountFraction.h"

namespace lmm {
    class SwapRateCalculator {
    public:
        SwapRateCalculator(
            const IYieldCurve& yieldCurve, const date_t& start,
            const Tenor& periods, const Tenor& termination)
        : _start(start), 
            _dates(makeTenorDates(start, periods, termination)),
            _rates(_dates.size(), 0.0)
        {
            const double firstDiscountFactor
                = yieldCurve.discountFactor(start, _dates(0));
            double sum = 0.0;
            for (std::size_t i = 1; i < _rates.size(); ++i) {
                const double df
                    = yieldCurve.discountFactor(start, _dates(i));
                sum += df * dayCountAct360(_dates(i - 1), _dates(i));
                _rates(i) 
                    = (firstDiscountFactor 
                        - yieldCurve.discountFactor(start, _dates(i)))
                        / sum;
            }
        }
        const double get(const Tenor& key) const
        {
            const date_t keyDate = addTenor(_start, key);
            if (std::find(_dates.begin(), _dates.end(), keyDate) 
                    == _dates.end()) {
                return 0.0;
            }
            const std::size_t index
                = std::find(_dates.begin(), _dates.end(), keyDate) 
                    - _dates.begin();
            return _rates(index);
        }

    private:
        const date_t _start;
        const ublas::vector<date_t> _dates;
        ublas::vector<double> _rates;

    };

}  // namespace llm

#endif // SWAPRATECALCULATOR_H_INCLUDED
