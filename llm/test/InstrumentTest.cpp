/*
 * InstrumentTest.cpp
 *
 *  Created on: 2015/05/10
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "../src/fwd.h"
#include "../src/Instrument.h"
#include "../src/InstrumentAdapter.h"

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
}

TEST(InstrumentTest, makeLegs) {
    const ublas::vector<lmm::date_t> legs
        = lmm::makeLegs(today, maturity, tenor);
    EXPECT_EQ(lmm::date_t(2015, 5, 9), legs(0));
    EXPECT_EQ(lmm::date_t(2015, 8, 9), legs(1));
    EXPECT_EQ(lmm::date_t(2015, 11, 9), legs(2));
    EXPECT_EQ(lmm::date_t(2016, 2, 9), legs(3));
    ASSERT_EQ(lmm::date_t(2016, 5, 8), legs(4));
}

TEST(InstrumentTest, makeCap) {
    EXPECT_EQ(cap.rates()(0), strike);
    EXPECT_EQ(cap.rates()(1), strike);
    EXPECT_EQ(cap.rates()(2), strike);
    EXPECT_EQ(cap.rates()(3), strike);
    ASSERT_EQ(cap.rates()(4), strike);
}

TEST(InstrumentTest, InstrumentAdapter) {
    std::vector<boost::shared_ptr<lmm::IInstrumentAdapter> >
        InstrumentAdapterPtrs;
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    EXPECT_EQ(lmm::date_t(2015, 5, 9), InstrumentAdapterPtrs[0]->legs()(0));
    EXPECT_EQ(lmm::date_t(2015, 8, 9), InstrumentAdapterPtrs[0]->legs()(1));
    EXPECT_EQ(lmm::date_t(2015, 11, 9), InstrumentAdapterPtrs[0]->legs()(2));
    EXPECT_EQ(lmm::date_t(2016, 2, 9), InstrumentAdapterPtrs[0]->legs()(3));
    ASSERT_EQ(lmm::date_t(2016, 5, 8), InstrumentAdapterPtrs[0]->legs()(4));
//    std::vector<boost::function <double(double)> targetFunctions
//        = lmm::makeTargetFunctions(InstrumentAdapter);
//
//    lmm::Calibrator calibrator;
//    const ublas::vector<double> initialValue(4, 0.0);
//    ublas::vector<double> parameters
//        = calibrator.optimize(targetFunctions, initialValue);
}

TEST(InstrumentTest, initialize) {
    std::vector<boost::shared_ptr<lmm::IInstrumentAdapter> >
        InstrumentAdapterPtrs;
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
    InstrumentAdapterPtrs.push_back(lmm::CapAdapter(cap).clone());
//    std::vector<boost::function <double(double)> targetFunctions
//        = lmm::makeTargetFunctions(InstrumentAdapter);
//
//    lmm::Calibrator calibrator;
//    const ublas::vector<double> initialValue(4, 0.0);
//    ublas::vector<double> parameters
//        = calibrator.optimize(targetFunctions, initialValue);
}
