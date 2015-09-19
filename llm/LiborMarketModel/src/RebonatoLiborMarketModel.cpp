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
#include "BlackScholesFormulas.h"

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

    double discountFactor(const double forwardInterestRate,
        const double maturity)
    {
        return 1.0 / (1.0 + maturity * forwardInterestRate);
    }

    double calcBlackScholesCapletsPrice(
        const std::size_t settlementIndex,
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& strikes,
        const ublas::vector<double>& capletVolatililies)
    {
        double capletPremium = 0.0;
        for(std::size_t i = 0; i < settlementIndex; ++i) {
            const double maturity = dayCountAct365(today, dates(i));
            const double tenor = dayCountAct365(dates(i), dates(i + 1));
            capletPremium += BlackFormula(
                liborForwardRates(i), strikes(i),
                capletVolatililies(i), maturity)
                * discountFactor(liborForwardRates(i), tenor);
        }
        return capletPremium;
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
        for(std::size_t i = 0; i <= settlementIndex; ++i) {
            const double maturity = dayCountAct365(today, dates(i));
            const double tenor = dayCountAct365(dates(i), dates(i + 1));
            capPremium += BlackFormula(
                liborForwardRates(i), strikes(i),
                capVolatilities(settlementIndex), maturity)
                * discountFactor(liborForwardRates(i), tenor);
        }
        return capPremium;
    }

    ublas::vector<double> makeCapletVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& liborForwardRates,
        const ublas::vector<double>& capStrikes,
        const ublas::vector<double>& capVolatilities)
    {
        ublas::vector<double> capletVolatilities(capVolatilities);
        for (std::size_t i = 0; i < capVolatilities.size(); ++i) {
            double capPremium = calcBlackScholesCapPrice(
                i, today, dates, liborForwardRates,
                capStrikes, capVolatilities);
            double capletPremium = calcBlackScholesCapletsPrice(
                i, today, dates, liborForwardRates,
                capStrikes, capletVolatilities);
            const double maturity = dayCountAct365(today, dates(i));
            const double tenor = dayCountAct365(dates(i), dates(i + 1));
            capletVolatilities(i) = ImpliedBlackVolatility(
                liborForwardRates(i), capStrikes(i),
                (capPremium - capletPremium)
                    / (discountFactor(liborForwardRates(i), tenor)),
                maturity);
        }
        return capletVolatilities;
    }
}  // namespace lmm
