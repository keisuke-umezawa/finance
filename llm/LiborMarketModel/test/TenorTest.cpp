/*
 * TenorTest.cpp
 *
 *  Created on: 2015/05/11
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include "fwd.h"
#include "Tenor.h"
#include "DiscountFactorTestData.h"

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

TEST(TenorTest, makeTenorDatesTest) {
    const lmm::Tenor periods(3, lmm::TenorUnit::Month);
    const lmm::Tenor termination(20, lmm::TenorUnit::Year);
    ublas::vector<lmm::date_t> dates
        = lmm::makeTenorDates(
            test_lmm::DiscountFactorTestData::today(),
            periods, termination);
    ASSERT_EQ(addTenor(test_lmm::DiscountFactorTestData::today(), periods),
        dates(0));
    ASSERT_EQ(addTenor(test_lmm::DiscountFactorTestData::today(), termination),
        *dates.crbegin());
}
