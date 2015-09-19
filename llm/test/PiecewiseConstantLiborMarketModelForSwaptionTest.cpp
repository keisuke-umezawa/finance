/*
 * PiecewiseConstantLiborMarketModel.cpp
 *
 *  Created on: 2015/06/24
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
#include "PiecewiseConstantLiborMarketModel.h"
#include "RebonatoLiborMarketModel.h"
#include "numeric.h"

namespace {
#include "SwaptionData.ipp"
}

TEST(PiecewiseConstantLiborMarketModelForSwaption, calcDiscountFactorChangeRatios) {
    const std::vector<ublas::matrix<double> > changeRatios
        = lmm::calcDiscountFactorChangeRatios(discountFactors, 5, 5);
    std::cout << changeRatios[0] << std::endl;
}

TEST(PiecewiseConstantLiborMarketModelForSwaption, calcLiborCovariance) {
    const std::vector<ublas::matrix<double> > changeRatios
        = lmm::calcDiscountFactorChangeRatios(discountFactors, 5, 5);
    const ublas::matrix<double> covariance
        = lmm::calcLiborCovariance(
            today, dates, swaptionVolatilities, changeRatios);
    std::cout << covariance << std::endl;
}
