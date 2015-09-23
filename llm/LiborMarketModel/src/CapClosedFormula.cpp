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

    double calcBlackScholesCapPrice(
        const std::size_t settlementIndex,
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& strikes,
        const ublas::vector<double>& capVolatilities)
    {
        double capPremium = 0.0;
        //for(std::size_t i = 0; i <= settlementIndex; ++i) {
        //    const double maturity = dayCountAct365(today, dates(i));
        //    const double tenor = dayCountAct365(dates(i), dates(i + 1));
        //    capPremium += BlackFormula(
        //        liborForwardRates(i), strikes(i),
        //        capVolatilities(settlementIndex), maturity)
        //        * discountFactor(liborForwardRates(i), tenor);
        //}
        return capPremium;
    }
}  // namespace lmm
