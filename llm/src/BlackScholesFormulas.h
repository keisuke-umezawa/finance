#ifndef BLACK_SCHOLES_FORMULAS_H_INCLUDED
#define BLACK_SCHOLES_FORMULAS_H_INCLUDED

namespace lmm {
    double BlackScholesCall(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double BlackScholesPut(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double BlackScholesDigitalCall(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double BlackScholesDigitalPut(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double BlackScholesCallVega(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double BlackFormula(
        double forward, double Strike, double Vol, double Expiry);
    double ImpliedBlackVolatility(double forward, double Strike,
        double premium, double Expiry);
}

#endif // BLACK_SCHOLES_FORMULAS_H_INCLUDED
