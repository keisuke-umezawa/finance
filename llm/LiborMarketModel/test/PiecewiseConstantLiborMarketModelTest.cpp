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
#include "CapClosedFormula.h"
#include "StripCapletVolatilities.h"
#include "CapTestData.h"
#include "DiscountFactorTestData.h"


TEST(PiecewiseConstantLiborMarketModel, initialize) {
    const std::size_t periodSize = 3;
    const std::size_t terminationSize = 20 * 12;
    const lmm::Tenor periods(periodSize, lmm::TenorUnit::Month);
    const lmm::Tenor termination(terminationSize, lmm::TenorUnit::Month);
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LogLinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    const lmm::LinearInterpolant capVolInterpolant(
        test_lmm::CapTestData::dates(),
        test_lmm::CapTestData::volatilities());

    const ublas::vector<double> capletVolatilities
        = lmm::stripCapletVolatilities(
            *yieldCurve,
            test_lmm::CapTestData::today(),
            periods,
            termination,
            capVolInterpolant);

    ublas::matrix<double> piecewiseConstantVolatilities
        = lmm::calcPiecewiseConstantVolatilities(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            capletVolatilities);

    //std::cout << capletVolatilities << std::endl;
    //std::cout << piecewiseConstantVolatilities << std::endl;
}
