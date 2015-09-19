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
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "invert.h"

namespace lmm {

    double RebonatoVolatilityFormula(const double tau,
        const double a, const double b, const double c, const double d);

    double TargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau,
        const double a, const double b, const double c, const double d);

    boost::function<double(double, double, double, double)>
    makeTargetRebonatoVolatilityFormula(
        const double targetVolatility, const double tau);

    double discountFactor(const double forwardInterestRate,
        const double maturity);

    ublas::vector<double> makeCapletVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& capStrikes,
        const ublas::vector<double>& capVolatililies);

    double calcBlackScholesCapPrice(
        const std::size_t settlementIndex,
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& strikes,
        const ublas::vector<double>& capVolatililies);
    double calcBlackScholesCapletsPrice(
        const std::size_t settlementIndex,
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& strikes,
        const ublas::vector<double>& capletVolatililies);
}  // namespace lmm



#endif // REBONATOLIBORMARKETMODEL_H_INCLUDED
