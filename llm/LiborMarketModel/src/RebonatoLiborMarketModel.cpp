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
#include "DayCountFraction.h"
#include "CapClosedFormula.h"
#include "StripCapletVolatilities.h"

namespace lmm {

    double RebonatoVolatilityFormula(const double tau,
        const double a, const double b, const double c, const double d)
    {
        return (a + b * tau) * std::exp(-c * tau) + d;
    }

    double TargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau,
        const double a, const double b, const double c, const double d)
    {
        return RebonatoVolatilityFormula(tau, a, b, c, d) - targetVolatility;
    }

    boost::function<double(double, double, double, double)>
    makeTargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau)
    {
        return boost::bind(&TargetRebonatoVolatilityFormula,
            targetVolatility, tau, _1, _2, _3, _4);
    }

}  // namespace lmm
