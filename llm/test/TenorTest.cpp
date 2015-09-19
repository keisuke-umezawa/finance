/*
 * TenorTest.cpp
 *
 *  Created on: 2015/05/11
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include "fwd.h"
#include "Tenor.h"

namespace {
    const lmm::date_t today(2015, 5, 9);
}

TEST(TenorTest, addDays) {
    ASSERT_EQ(lmm::date_t(2015, 5, 19), lmm::addDays(today, 10));
}

TEST(TenorTest, addMonths) {
    ASSERT_EQ(lmm::date_t(2016, 3, 9), lmm::addMonths(today, 10));
}

TEST(TenorTest, addYears) {
    ASSERT_EQ(lmm::date_t(2025, 5, 9), lmm::addYears(today, 10));
}

TEST(TenorTest, addTenorByMonth) {
    ASSERT_EQ(lmm::date_t(2015, 8, 9),
        lmm::addTenor(today, lmm::Tenor(3, lmm::TenorUnit::Month)));
}

TEST(TenorTest, addTenorByYear) {
    ASSERT_EQ(lmm::date_t(2018, 5, 9),
        lmm::addTenor(today, lmm::Tenor(3, lmm::TenorUnit::Year)));
}
