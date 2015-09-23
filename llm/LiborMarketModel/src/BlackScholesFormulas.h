#ifndef BLACK_SCHOLES_FORMULAS_H_INCLUDED
#define BLACK_SCHOLES_FORMULAS_H_INCLUDED

namespace lmm {
    double calculateBlackScholesCall(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double calculateBlackScholesPut(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double calculateBlackScholesDigitalCall(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double calculateBlackScholesDigitalPut(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double calculateBlackScholesCallVega(
        double Spot, double Strike, double r, double d,
        double Vol, double Expiry);
    double calculateBlackFormula(
        double forward, double Strike, double Vol, double Expiry);
    double calculateImpliedBlackVolatility(double forward, double Strike,
        double premium, double Expiry);
}

#endif // BLACK_SCHOLES_FORMULAS_H_INCLUDED
