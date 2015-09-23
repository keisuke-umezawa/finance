/*
 *
 * RebonatoLiborMarketModel.cpp
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#include "RebonatoLiborMarketModel.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "YieldCurve.h"
#include "DayCountFraction.h"
#include "BlackScholesFormulas.h"

namespace lmm {
    const double calculateBsCapletPrice(
        const IYieldCurve& yieldCurve,
        const double forwardRate,
        const double strike,
        const double volatility,
        const date_t& today,
        const date_t& start,
        const date_t& end)
    {
        const double maturity = dayCountAct360(today, start);
        const double premium 
            = calculateBlackFormula(
                    forwardRate, strike, volatility, maturity)
                * yieldCurve.discountFactor(today, start) 
                * dayCountAct360(start, end);
        return premium;
    }
    const double calculateBsCapletsPrice(
        const IYieldCurve& yieldCurve,
        const IYieldCurve& forwardCurve,
        const double strike,
        const ublas::vector<double>& volatilities,
        const date_t& today,
        const ublas::vector<date_t>& dates)
    {
        double premium = 0.0;
        for (std::size_t i = 1; i < dates.size(); ++i) {
            premium += calculateBsCapletPrice(
                yieldCurve, 
                forwardRate(forwardCurve, today, dates(i - 1), dates(i)),
                strike, volatilities(i - 1),
                today, dates(i - 1), dates(i));
        }
        return premium;
    }

    const double calculateBsCapPrice(
        const IYieldCurve& yieldCurve,
        const IYieldCurve& forwardCurve,
        const double strike,
        const double volatility,
        const date_t& today,
        const ublas::vector<date_t>& dates)
    {
        double premium = 0.0;
        for (std::size_t i = 1; i < dates.size(); ++i) {
            premium += calculateBsCapletPrice(
                yieldCurve, 
                forwardRate(forwardCurve, today, dates(i - 1), dates(i)),
                strike, volatility,
                today, dates(i - 1), dates(i));
        }
        return premium;
    }
}  // namespace lmm
