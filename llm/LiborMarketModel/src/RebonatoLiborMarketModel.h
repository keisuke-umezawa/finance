/*
 * RebonatoLiborMarketModel.h
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#ifndef REBONATOLIBORMARKETMODEL_H_INCLUDED
#define REBONATOLIBORMARKETMODEL_H_INCLUDED

#include <cmath>
#include <boost/function.hpp>
#include "fwd.h"

namespace lmm {

    double RebonatoVolatilityFormula(const double tau,
        const double a, const double b, const double c, const double d);

    double TargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau,
        const double a, const double b, const double c, const double d);

    boost::function<double(double, double, double, double)>
    makeTargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau);

}  // namespace lmm



#endif // REBONATOLIBORMARKETMODEL_H_INCLUDED
