#include <gtest/gtest.h>
#include "fwd.h"
#include "Tenor.h"
#include "StripCapletVolatilities.h"
#include "CapTestData.h"
#include "YieldCurveMock.h"
#include "InterpolantMock.h"
#include "Interpolant.h"
#include "DiscountFactorTestData.h"

using namespace ::testing;

TEST(StripCapletVolatilitiesTest, stripCapletVolatilitiesTest) {
    const std::size_t periodSize = 3;
    const std::size_t terminationSize = 9;
    const lmm::Tenor periods(periodSize, lmm::TenorUnit::Month);
    const lmm::Tenor termination(terminationSize, lmm::TenorUnit::Month);

    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnConstantDiscountFactor));
    const test_lmm::InterpolantMock capVolInterpolant;
    const double vol = 0.1;
    EXPECT_CALL(capVolInterpolant, doOperator(_))
        .WillRepeatedly(Return(vol));

    const ublas::vector<double> capletVolatilities
        = lmm::stripCapletVolatilities(
            yieldCurve,
            test_lmm::CapTestData::today(),
            periods,
            termination,
            capVolInterpolant);

    const std::size_t expectedSize = terminationSize / periodSize - 1;
    ASSERT_EQ(expectedSize, capletVolatilities.size());
    for (std::size_t i = 0; i < capletVolatilities.size(); ++i) {
        ASSERT_NEAR(vol, capletVolatilities(i), 1e-10);
    }
}
TEST(StripCapletVolatilitiesTest, stripCapletVolatilitiesTestByRegression) {
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
    const std::size_t expectedSize = terminationSize / periodSize - 1;
    ASSERT_EQ(expectedSize, capletVolatilities.size());
    ASSERT_NEAR(test_lmm::CapTestData::volatilities()(0), 
        capletVolatilities(0), 1e-10);
    ASSERT_NEAR(test_lmm::CapTestData::volatilities()(0), 
        capletVolatilities(1), 1e-10);
}
