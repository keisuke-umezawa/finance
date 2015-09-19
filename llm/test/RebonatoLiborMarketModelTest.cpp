/*
 * RebonatoLiborMarketModel.cpp
 *
 *  Created on: 2015/05/26
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "fwd.h"
#include "RebonatoLiborMarketModel.h"
#include "numeric.h"


namespace {
#include "MarketData.ipp"
}


TEST(RebonatoLiborMarketModelTest, calibration) {
    const ublas::vector<double> initials(4, 1.0);
    std::vector<boost::function<double(double, double, double, double)> >
        functions;
    functions.push_back(boost::bind(&lmm::RebonatoVolatilityFormula,
        0.5, _1, _2, _3, _4));
    functions.push_back(boost::bind(&lmm::RebonatoVolatilityFormula,
        1.0, _1, _2, _3, _4));
    functions.push_back(boost::bind(&lmm::RebonatoVolatilityFormula,
        1.5, _1, _2, _3, _4));
    functions.push_back(boost::bind(&lmm::RebonatoVolatilityFormula,
        2.0, _1, _2, _3, _4));
    ublas::vector<double> results(numeric::calculate(functions,
        numeric::newton(functions, initials, 100, 1e-10)));
    EXPECT_NEAR(results(0), 0.0, 1e-5);
    EXPECT_NEAR(results(1), 0.0, 1e-5);
    EXPECT_NEAR(results(2), 0.0, 1e-5);
    ASSERT_NEAR(results(3), 0.0, 1e-5);
}

TEST(RebonatoLiborMarketModelTest, testMakeCapletVolatilities) {
    const ublas::vector<double> capletVolatilities
        = lmm::makeCapletVolatilities(
            today, dates, liborForwardRates, capStrikes, capVolatilities);
    ASSERT_NEAR(capletVolatilities(0), 1.53, 1e-5);
    ASSERT_NEAR(capletVolatilities(19), 0.284528, 1e-5);
}

TEST(RebonatoLiborMarketModelTest, calibrationToValatility) {
    const ublas::vector<double> capletVolatilities
        = lmm::makeCapletVolatilities(
            today, dates, liborForwardRates, capStrikes, capVolatilities);

    const ublas::vector<double> initials(4, 1.0);
    std::vector<boost::function<double(double, double, double, double)> >
        functions;
    functions.push_back(
        lmm::makeTargetRebonatoVolatilityFormula(capVolatilities(0), 0.5));
    functions.push_back(
        lmm::makeTargetRebonatoVolatilityFormula(capVolatilities(1), 1.0));
    functions.push_back(
        lmm::makeTargetRebonatoVolatilityFormula(capVolatilities(2), 1.5));
    functions.push_back(
        lmm::makeTargetRebonatoVolatilityFormula(capVolatilities(3), 2.0));
    ublas::vector<double> parameters
        = numeric::newton(functions, initials, 100, 1e-10);
    ublas::vector<double> results(numeric::calculate(functions, parameters));
    EXPECT_NEAR(results(0), 0.0, 1e-5);
    EXPECT_NEAR(results(1), 0.0, 1e-5);
    EXPECT_NEAR(results(2), 0.0, 1e-5);
    ASSERT_NEAR(results(3), 0.0, 1e-5);
}

