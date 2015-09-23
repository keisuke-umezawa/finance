/*
 * RebonatoLiborMarketModel.h
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#ifndef REBONATOLIBORMARKETMODEL_H_INCLUDED
#define REBONATOLIBORMARKETMODEL_H_INCLUDED

#include <algorithm>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include "fwd.h"
#include "BlackScholesFormulas.h"
#include "YieldCurve.h"
#include "Tenor.h"
#include "LinearInterpolant.h"
#include "SwapRateCalculator.h"
#include "CapClosedFormula.h"

namespace lmm {
    ublas::vector<double> stripCapletVolatilities(
        const IYieldCurve& yieldCurve,
        const date_t& today,
        const Tenor& periods,   
        const Tenor& termination,
        const IInterpolant& capVolatilityInterpolant)
    {
        const ublas::vector<date_t> dates
            = makeTenorDates(today, periods, termination);
        const lmm::SwapRateCalculator calculator(yieldCurve, today, dates);
        ublas::vector<double> capletVolatilities(dates.size() - 1);
        ublas::vector<double> swapRates(dates.size() - 1);
        for (std::size_t i = 0; i + 1 < dates.size(); ++i) {
            const date_t& start = dates(i);
            const date_t& end = dates(i + 1);
            const double swapRate = calculator.get(end);
            const double capVol = capVolatilityInterpolant(end);

            double capPremium = calculateBsCapPrice(
                yieldCurve, yieldCurve, swapRate, capVol, today, 
                ublas::subrange(dates, 0, i + 2));
            double capletPremium = calculateBsCapletsPrice(
                yieldCurve, yieldCurve,
                swapRate,
                ublas::subrange(capletVolatilities, 0, i),
                today,
                ublas::subrange(dates, 0, i + 1));
            const double maturity = dayCountAct360(today, start);
            capletVolatilities(i) = calculateImpliedBlackVolatility(
                forwardRate(yieldCurve, today, start, end), 
                swapRate,
                (capPremium - capletPremium)
                / (yieldCurve.discountFactor(today, start)
                    * dayCountAct360(start, end)),
                maturity);
            swapRates(i) = swapRate;
        }
        return capletVolatilities;
    }
}  // namespace lmm



#endif // REBONATOLIBORMARKETMODEL_H_INCLUDED
