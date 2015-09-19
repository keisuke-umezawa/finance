#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "BlackScholesFormulas.h"
#include "Normals.h"
#include "numeric.h"

namespace lmm {
    double BlackScholesCall(
        double spot, double strike, double r, double d, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = std::log(spot / strike);
        double d1 = (moneyness + (r - d) * maturity
            + 0.5 * standardDeviation * standardDeviation) / standardDeviation;
        double d2 = d1 - standardDeviation;

        return spot * exp(-d * maturity) * CumulativeNormal(d1)
            - strike * std::exp(-r * maturity) * CumulativeNormal(d2);
    }

    double BlackScholesPut(
        double spot, double strike, double r, double d, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = log(spot / strike);
        double d1 = (moneyness + (r - d) * maturity + 0.5 * standardDeviation * standardDeviation)
            / standardDeviation;
        double d2 = d1 - standardDeviation;

        return strike * std::exp(-r * maturity) * (1.0 - CumulativeNormal(d2))
            - spot * std::exp(-d * maturity) * (1.0 - CumulativeNormal(d1));
    }

    double BlackScholesDigitalCall(
        double spot, double strike, double r, double d, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = std::log(spot / strike);
        double d2 = (moneyness + (r - d) * maturity
            - 0.5 * standardDeviation * standardDeviation) / standardDeviation;

        return std::exp(-r * maturity) * CumulativeNormal(d2);
    }

    double BlackScholesDigitalPut(
        double spot, double strike, double r, double d, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = std::log(spot / strike);
        double d2 = (moneyness + (r - d) * maturity
            - 0.5 * standardDeviation * standardDeviation) / standardDeviation;

        return std::exp(-r * maturity) * (1.0 - CumulativeNormal(d2));
    }

    double BlackScholesCallVega(
        double spot, double strike, double r, double d, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = std::log(spot / strike);
        double d1 = (moneyness + (r - d) * maturity
            + 0.5 * standardDeviation * standardDeviation) / standardDeviation;

        return spot * std::exp(-d * maturity) * std::sqrt(maturity) * NormalDensity(d1);
    }

    double BlackFormula(double forward, double strike, double vol, double maturity)
    {
        double standardDeviation = vol * std::sqrt(maturity);
        double moneyness = std::log(forward / strike);
        double d1 = (moneyness + 0.5 * standardDeviation * standardDeviation)
            / standardDeviation;
        double d2 = d1 - standardDeviation;

        return forward * CumulativeNormal(d1) - strike * CumulativeNormal(d2);
    }

    double ImpliedBlackVolatility(
        double forward, double strike, double premium, double maturity)
    {
        const boost::function<double(double)> f
            = numeric::makeTargetFunction(
                boost::bind(&lmm::BlackFormula, forward, strike, _1, maturity),
                premium);
        const double volatility = numeric::newton(f,
            std::sqrt(2.0 * M_PI / maturity) * premium / forward, 1000, 1e-10);
        return volatility;
    }
} // namespace lmm {
