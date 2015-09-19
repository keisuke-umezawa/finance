/*
 * BlackScholesFomulasTest.cpp
 *
 *  Created on: 2015/06/07
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include "BlackScholesFormulas.h"

TEST(BlackScholesFomulasTest, testImpliedBlackVolatility) {
    const double forward = 0.1;
    const double strike = 0.1;
    const double expiry = 1.0;
    const double volatility = 1.0;
    const double premium = lmm::BlackFormula(forward, strike, volatility, expiry);

    const double impliedVolatility =
        lmm::ImpliedBlackVolatility(forward, strike, premium, expiry);
    ASSERT_NEAR(volatility, impliedVolatility, 1e-10);
}
