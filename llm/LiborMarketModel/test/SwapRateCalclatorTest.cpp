#include <gtest/gtest.h>
#include "fwd.h"
#include "Tenor.h"
#include "SwapRateCalculator.h"
#include "YieldCurve.h"
#include "YieldCurveMock.h"
#include "Tenor.h"
#include "DaycountFraction.h"
#include "DiscountFactorTestData.h"


using ::testing::_;
using ::testing::Invoke;


TEST(SwapRateCalculatorTest, constructSwapRateCalculatorTest) {
    const lmm::Tenor periods(3, lmm::TenorUnit::Month);
    const lmm::Tenor termination(20, lmm::TenorUnit::Year);
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnZeroOver6Months));
    const ublas::vector<lmm::date_t> dates = makeTenorDates(
        test_lmm::DiscountFactorTestData::today(), periods, termination);
    const lmm::SwapRateCalculator calculator(
        yieldCurve,
        test_lmm::DiscountFactorTestData::today(), dates);

    {
        const lmm::date_t target
            = lmm::addTenor(test_lmm::DiscountFactorTestData::today(),
                lmm::Tenor(6, lmm::TenorUnit::Month));
        const double expected = 1.0 / lmm::dayCountAct360(
            lmm::addMonths(test_lmm::DiscountFactorTestData::today(), 3),
            lmm::addMonths(test_lmm::DiscountFactorTestData::today(), 6));
        ASSERT_DOUBLE_EQ(expected, calculator.get(target));
    }
}

TEST(SwapRateCalculatorTest, swapRateCalculatorTestByRegression) {
    const lmm::Tenor periods(3, lmm::TenorUnit::Month);
    const lmm::Tenor termination(20, lmm::TenorUnit::Year);
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    const ublas::vector<lmm::date_t> dates = makeTenorDates(
        test_lmm::DiscountFactorTestData::today(), periods, termination);
    const lmm::SwapRateCalculator calculator(
        *yieldCurve,
        test_lmm::DiscountFactorTestData::today(), dates);
    {
        const lmm::date_t target
            = lmm::addTenor(test_lmm::DiscountFactorTestData::today(),
                lmm::Tenor(6, lmm::TenorUnit::Month));
        const double expected = 0.021914959627962867;
        ASSERT_DOUBLE_EQ(expected, calculator.get(target));
    }
    {
        const lmm::date_t target
            = lmm::addTenor(test_lmm::DiscountFactorTestData::today(),
                lmm::Tenor(120, lmm::TenorUnit::Month));
        const double expected = 0.035766656027881392;
        ASSERT_DOUBLE_EQ(expected, calculator.get(target));
    }
}