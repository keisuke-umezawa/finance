#include <gmock/gmock.h>
#include "fwd.h"
#include "DayCountFraction.h"
#include "SwaptionCovariance.h"
#include "DiscountFactorRatio.h"
#include "DiscountFactorTestData.h"
#include "SwaptionTestData.h"
#include "YieldCurveMock.h"
#include "Tenor.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

TEST(SwaptionCovarianceTest, calculateDiagonalElement) {
    const double swaptoinVolatility = 0.1;
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const lmm::Tenor tenor(1, lmm::TenorUnit::Year);
    const boost::function<double(lmm::date_t)> lambda
        = boost::bind(&lmm::dayCountAct360, today, _1);

    const lmm::date_t tenorDate = lmm::addTenor(today, tenor);
    const double expected = lmm::dayCountAct360(today, tenorDate)
        * swaptoinVolatility * swaptoinVolatility / lambda(tenorDate);
    ASSERT_DOUBLE_EQ(expected,
        lmm::calculateDiagonalElement(
            swaptoinVolatility, today, tenor, lambda));
}
TEST(SwaptionCovarianceTest, calculateNonDiagonalElement) {
    const double swaptoinVolatility = 0.1;
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnConstantDiscountFactor));
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const lmm::Tenor tenor(1, lmm::TenorUnit::Year);
    const ublas::vector<lmm::Tenor> tenors
        = test_lmm::SwaptionTestData::tenors();
    const lmm::DiscountFactorRatioGenerator generator(
        yieldCurve, today, tenors, tenors);
    const boost::function<double(lmm::date_t)> lambda
        = boost::bind(&lmm::dayCountAct360, today, _1);

    const lmm::date_t tenorDate = lmm::addTenor(today, tenor);
    const double expected = lmm::dayCountAct360(today, tenorDate)
        * swaptoinVolatility * swaptoinVolatility / lambda(tenorDate);
    lmm::calculateNonDiagonalElement(
        swaptoinVolatility, generator, today, tenor, lambda);
}

TEST(SwaptionCovarianceTest, calculateSwaptionCovariance)
{
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnConstantDiscountFactor));
    const ublas::matrix<double> swaptionVolatilities
        = test_lmm::SwaptionTestData::volatilities();
    const lmm::date_t today
        = test_lmm::SwaptionTestData::today();
    const ublas::vector<lmm::Tenor> tenors
        = test_lmm::SwaptionTestData::tenors();
    const lmm::DiscountFactorRatioGenerator generator(
        yieldCurve, today, tenors, tenors);
    const boost::function<double(lmm::date_t)> lambda
        = boost::bind(&lmm::dayCountAct360, today, _1);

    const ublas::matrix<double> covariance
        = lmm::calculateSwaptionCovariance(
            swaptionVolatilities, generator, today, tenors, lambda);
    ASSERT_EQ(tenors.size(), covariance.size1());
    ASSERT_EQ(tenors.size(), covariance.size2());

    const lmm::Tenor start(1, lmm::TenorUnit::Year);
    const lmm::Tenor period(1, lmm::TenorUnit::Year);
    const double expected = lmm::calculateDiagonalElement(
        swaptionVolatilities(
            lmm::toIndex(start, tenors),
            lmm::toIndex(period, tenors)), today, start, lambda);
    ASSERT_DOUBLE_EQ(expected, covariance(
        lmm::toIndex(start, tenors), lmm::toIndex(start, tenors)));
}