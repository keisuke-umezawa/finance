#include <gmock/gmock.h>
#include "YieldCurve.h"
#include "YieldCurveMock.h"
#include "CapClosedFormula.h"
#include "DayCountFraction.h"


TEST(CapClosedFormulaTest, calculateBsCapletPrice) {
    const lmm::date_t today(2000, 1, 1);
    const lmm::date_t start = lmm::addMonths(today, 3);
    const lmm::date_t end = lmm::addMonths(today, 6);
    const test_lmm::YieldCurveMock yieldCurve;
    EXPECT_CALL(yieldCurve, doDiscountFactor(_, _))
        .WillRepeatedly(Invoke(test_lmm::returnZeroOver6Months));
    const double vol = 0.1;
    const double strike = 0.1;
    const double forwardRate = 10000.0;

    const double expected 
        =  yieldCurve.discountFactor(today, start) 
            * lmm::dayCountAct360(start, end) 
            * (forwardRate - strike);
    
    ASSERT_DOUBLE_EQ(expected, 
        lmm::calculateBsCapletPrice(
            yieldCurve, forwardRate, strike, vol, today, start, end));
}