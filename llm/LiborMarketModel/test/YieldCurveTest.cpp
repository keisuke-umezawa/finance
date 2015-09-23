#include <gmock/gmock.h>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "YieldCurve.h"
#include "YieldCurveMock.h"
#include "LinearInterpolant.h"
#include "DayCountFraction.h"
#include "DiscountFactorTestData.h"

using ::testing::_;
using ::testing::Invoke;

TEST(YieldCurveTest, testConstantRateYieldCurve) {
    const lmm::date_t start(2014, 2, 3);
    const lmm::date_t end(2015, 2, 3);
    const double rate = 0.01;

    const boost::function<double(lmm::date_t, lmm::date_t)> dayCountFractoion
        = boost::bind(&lmm::dayCountAct365, _1, _2);
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = boost::make_shared<lmm::ConstantRateYieldCurve>(
            rate, dayCountFractoion);
    ASSERT_DOUBLE_EQ(std::exp(-rate), yieldCurve->discountFactor(start, end));
}

TEST(YieldCurveTest, testPiecewiseYieldCurve) {
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    {
        ASSERT_DOUBLE_EQ(1.0, yieldCurve->discountFactor(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::today()));
    }
    {
        const lmm::date_t start(2006, 1, 1);
        ASSERT_DOUBLE_EQ(1.0, yieldCurve->discountFactor(
            start, start));
    }
    {
        const std::size_t index = 5;
        const lmm::date_t start
            = test_lmm::DiscountFactorTestData::today();
        const lmm::date_t end
            = test_lmm::DiscountFactorTestData::dates()(index);
        const double expected
            = test_lmm::DiscountFactorTestData::discountFactors()(index);
        ASSERT_DOUBLE_EQ(expected, yieldCurve->discountFactor(start, end));
    }
}

TEST(YieldCurveTest, testLinearYieldCurveByRegression) {
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    {
        const lmm::date_t start
            = test_lmm::DiscountFactorTestData::today();
        const lmm::date_t end(2007, 7, 25); // 2Y6M
        const double expected = 0.9363837304109589; // 0.9369436;
        ASSERT_DOUBLE_EQ(expected, yieldCurve->discountFactor(start, end));
    }
}
TEST(YieldCurveTest, testLogLinearYieldCurveByRegression) {
    const boost::shared_ptr<const lmm::IYieldCurve> yieldCurve
        = lmm::makePiecewiseYieldCurve<lmm::LogLinearInterpolant>(
            test_lmm::DiscountFactorTestData::today(),
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());
    {
        const lmm::date_t start
            = test_lmm::DiscountFactorTestData::today();
        const lmm::date_t end(2007, 7, 25); // 2Y6M
        const double expected = 0.93627153502286697;
        ASSERT_DOUBLE_EQ(expected, yieldCurve->discountFactor(start, end));
    }
}
TEST(YieldCurveTest, testForwardRate) {
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnZeroOver6Months));
    const lmm::date_t today(2000, 1, 1);
    const lmm::date_t start = lmm::addMonths(today, 3);
    const lmm::date_t end = lmm::addMonths(today, 6);
    const double expected = 1.0 / lmm::dayCountAct360(start, end);
    ASSERT_DOUBLE_EQ(expected, 
        lmm::forwardRate(yieldCurve, today, start, end));
}