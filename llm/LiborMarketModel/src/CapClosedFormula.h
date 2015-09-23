/*
 * RebonatoLiborMarketModel.h
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#ifndef CAPCLOSEDFORMULA_H_INCLUDED
#define CAPCLOSEDFORMULA_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"
#include "YieldCurve.h"

namespace lmm {
    double calcBlackScholesCapPrice(
        const std::size_t settlementIndex,
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& strikes,
        const ublas::vector<double>& capVolatililies);
    const double calculateBsCapletPrice(
        const IYieldCurve& yieldCurve,
        const double forwardRate,
        const double strike,
        const double volatility,
        const date_t& today,
        const date_t& start,
        const date_t& end);
}  // namespace lmm



#endif // CAPCLOSEDFORMULA_H_INCLUDED
