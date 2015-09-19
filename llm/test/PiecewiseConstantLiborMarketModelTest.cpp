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
#include "MarketData.ipp"
}

TEST(PiecewiseConstantLiborMarketModel, initialize) {
    const ublas::vector<double> capletVolatilities
        = lmm::makeCapletVolatilities(
            today, dates, liborForwardRates, capStrikes, capVolatilities);

    ublas::matrix<double> piecewiseConstantVolatilities
        = lmm::calcPiecewiseConstantVolatilities(today, dates,
            capletVolatilities);

    std::cout << capletVolatilities << std::endl;
    std::cout << piecewiseConstantVolatilities << std::endl;
}
