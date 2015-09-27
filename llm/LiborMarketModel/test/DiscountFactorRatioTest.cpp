#include <gtest/gtest.h>
#include <numeric>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include "fwd.h"
#include "DiscountFactorTestData.h"
#include "SwaptionTestData.h"
#include "DiscountFactorRatio.h"
#include "YieldCurveMock.h"
#include "linalg/vector_proxy.h"

namespace ublas = boost::numeric::ublas;
using namespace ::testing;

TEST(DiscountFactorRatioTest, makeDiscountFactorRatios) {
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const ublas::vector<lmm::Tenor> tenors
        = ublas::subrange(test_lmm::SwaptionTestData::tenors(), 0, 2);
    const lmm::Tenor startTenor = lmm::Tenor(1, lmm::TenorUnit::Year);
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnConstantDiscountFactor));
    const ublas::vector<double> ratios
        = lmm::makeDiscountFactorRatios(
            yieldCurve, today, startTenor, tenors);
    ASSERT_EQ(2u, ratios.size());
    const double sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
    ASSERT_DOUBLE_EQ(1.0, sum);
}
TEST(DiscountFactorRatioTest, toIndex) {
    const std::size_t expected = 2;
    const ublas::vector<lmm::Tenor> tenors
        = test_lmm::SwaptionTestData::tenors();
    const lmm::Tenor tenor = tenors(expected);
    ASSERT_EQ(expected, lmm::toIndex(tenor, tenors));
}

TEST(DiscountFactorRatioTest, constructTest) {
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnConstantDiscountFactor));
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const ublas::vector<lmm::Tenor> startTenors
        = test_lmm::SwaptionTestData::tenors();
    const ublas::vector<lmm::Tenor> periodTenors
        = test_lmm::SwaptionTestData::tenors();

    const lmm::DiscountFactorRatioGenerator generator(
        yieldCurve, today, startTenors, periodTenors);
    {
        const ublas::vector<double> ratios
            = generator.get(startTenors(0), periodTenors(0));
        ASSERT_EQ(1u, ratios.size());
        const double sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
        ASSERT_DOUBLE_EQ(1.0, sum);
    }
    {
        const ublas::vector<double> ratios
            = generator.get(startTenors(0), periodTenors(1));
        ASSERT_EQ(2u, ratios.size());
        const double sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
        ASSERT_DOUBLE_EQ(1.0, sum);
    }
}
TEST(DiscountFactorRatioTest, getTestByRegression) {
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const ublas::vector<lmm::Tenor> startTenors
        = test_lmm::SwaptionTestData::tenors();
    const ublas::vector<lmm::Tenor> periodTenors
        = test_lmm::SwaptionTestData::tenors();

    const lmm::DiscountFactorRatioGenerator generator(
        *yieldCurve, today, startTenors, periodTenors);
    for (std::size_t i = 0; i < startTenors.size(); ++i) {
        ublas::vector<double> ratios
            = generator.get(startTenors(0), startTenors(i));
        ASSERT_EQ(i + 1, ratios.size());
        const double sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
        ASSERT_DOUBLE_EQ(1.0, sum);
    }
}
