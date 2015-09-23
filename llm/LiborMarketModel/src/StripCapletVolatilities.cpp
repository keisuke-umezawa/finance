/*
 * RebonatoLiborMarketModel.h
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#ifndef REBONATOLIBORMARKETMODEL_H_INCLUDED
#define REBONATOLIBORMARKETMODEL_H_INCLUDED

#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "fwd.h"
#include "YieldCurve.h"
#include "DayCountFraction.h"
#include "BlackScholesFormulas.h"
#include "CapClosedFormula.h"

namespace lmm {
    ublas::vector<double> makeCapletVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& capStrikes,
        const ublas::vector<double>& capVolatilities,
        const IYieldCurve& yieldCurve)
    {
        ublas::vector<double> capletVolatilities(capVolatilities);
        //for (std::size_t i = 0; i < capVolatilities.size(); ++i) {
        //    double capPremium = calcBlackScholesCapPrice(
        //        i, today, dates, liborForwardRates,
        //        capStrikes, capVolatilities);
        //    double capletPremium = calcBlackScholesCapletsPrice(
        //        i, today, dates, liborForwardRates,
        //        capStrikes, capletVolatilities);
        //    const double maturity = dayCountAct365(today, dates(i));
        //    const double tenor = dayCountAct365(dates(i), dates(i + 1));
        //    capletVolatilities(i) = ImpliedBlackVolatility(
        //        liborForwardRates(i), capStrikes(i),
        //        (capPremium - capletPremium)
        //            / (yieldCurve.discountFactor(dates(i), dates(i + 1))),
        //        maturity);
        //}
        return capletVolatilities;
    }
}  // namespace lmm



#endif // REBONATOLIBORMARKETMODEL_H_INCLUDED
