/*
 * InstrumentVisitorTest.cpp
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include "../src/fwd.h"
#include "../src/Instrument.h"
#include "../src/InstrumentVisitor.h"
#include "../src/InstrumentAccepter.h"

namespace ublas = boost::numeric::ublas;

namespace {
    const double strike = 0.01;
    const lmm::date_t today(2015, 5, 9);
    const lmm::date_t start(2015, 11, 9);
    const lmm::date_t end(2016, 5, 9);
    const lmm::date_t maturity(2016, 5, 8);
    const lmm::Tenor tenor(3, lmm::TenorUnit::Month);
    const lmm::Caplet caplet(strike, today, start, end);
    const lmm::Cap cap
        = lmm::makeCap(strike, today, maturity, tenor);
    const double volatility = 0.1;
    const double rate = 0.1;
}

TEST(InstrumentVisitorTest, evaluateCaplet) {
    lmm::CapletAccepter capletAccepter(caplet);
    lmm::PremiumPricer pricer(rate, volatility);
    capletAccepter.accept(pricer);
    ASSERT_NEAR(0.09, pricer.premium(), 1e-3);
}

TEST(InstrumentVisitorTest, evaluateCap) {
    lmm::CapAccepter capAccepter(cap);
    lmm::PremiumPricer pricer(rate, volatility);
    capAccepter.accept(pricer);
    ASSERT_EQ(1.0, pricer.premium());
}
