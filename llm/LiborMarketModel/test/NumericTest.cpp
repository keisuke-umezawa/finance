/*
 * NumericTest.cpp
 *
 *  Created on: 2015/06/07
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

TEST(NumericTest, integralRebonatoVolatilityFormula) {
    const std::size_t divisionSize = 1000000;
    const boost::function<double(double)> f
        = boost::bind(&lmm::RebonatoVolatilityFormula,
            _1, 1.0, 0.0, -1.0, 2.0);

    ASSERT_NEAR(
        numeric::integral(f, 0.0, 5.0, divisionSize),
        std::exp(5.0) + 9.0,
        1e-3);
}

TEST(NumericTest, derivative1d) {
    const boost::function<double(double)> f
        = boost::bind<double, double>(&std::exp, _1);
    ASSERT_NEAR(numeric::derivative(f, 1.0, 1e-10), std::exp(1.0), 1e-6);
}

TEST(NumericTest, derivative4d) {
    const boost::function<double(double, double, double, double)> f
        = boost::bind(&lmm::RebonatoVolatilityFormula, 0.5,
            _1, _2, _3, _4);
    const ublas::vector<double> initials(4, 0.0);
    const ublas::vector<double> results(numeric::derivative(f, initials, 1e-10));
    EXPECT_NEAR(results(0), 1.0, 1e-10);
    EXPECT_NEAR(results(1), 0.5, 1e-10);
    EXPECT_NEAR(results(2), 0.0, 1e-10);
    ASSERT_NEAR(results(3), 1.0, 1e-10);
}

TEST(NumericTest, jacobi) {
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
    ublas::matrix<double> results(numeric::jacobi(functions, initials, 1e-10));
    EXPECT_NEAR(results(0, 0), std::exp(-0.5), 1e-5);
    EXPECT_NEAR(results(1, 1), std::exp(-1.0), 1e-5);
    EXPECT_NEAR(results(2, 2), -1.5 * 2.5 * std::exp(-1.5), 1e-5);
    ASSERT_NEAR(results(3, 3), 1.0, 1e-5);
}

TEST(NumericTest, calculate) {
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
    ublas::vector<double> results(numeric::calculate(functions, initials));
    EXPECT_NEAR(results(0), 1.5 * std::exp(-0.5) + 1.0, 1e-5);
    EXPECT_NEAR(results(1), 2.0 * std::exp(-1.0) + 1.0, 1e-5);
    EXPECT_NEAR(results(2), 2.5 * std::exp(-1.5) + 1.0, 1e-5);
    ASSERT_NEAR(results(3), 3.0 * std::exp(-2.0) + 1.0, 1e-5);
}
