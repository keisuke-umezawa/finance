/*
 * YieldCurveTest.cpp
 *
 *  Created on: 2015/05/15
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "YieldCurve.h"
#include "DayCountFraction.h"

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
