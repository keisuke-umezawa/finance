/*
 * TenorTest.cpp
 *
 *  Created on: 2015/05/11
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"
#include "LinearInterpolant.h"
#include "DiscountFactorTestData.h"


TEST(TenorTest, constructLinearInterpolant) {
    const lmm::LinearInterpolant interpolant(
            test_lmm::DiscountFactorTestData::dates(),
            test_lmm::DiscountFactorTestData::discountFactors());

    {
        const lmm::date_t x(2000, 1, 1);
        const double expected 
            = test_lmm::DiscountFactorTestData::discountFactors()(0);
        ASSERT_DOUBLE_EQ(expected, interpolant(x));
    }
    {
        const lmm::date_t x(2100, 1, 1);
        const double expected 
            = test_lmm::DiscountFactorTestData::discountFactors()(
                test_lmm::DiscountFactorTestData::discountFactors().size() - 1);
        ASSERT_DOUBLE_EQ(expected, interpolant(x));
    }
    {
        const std::size_t index = 4;
        const lmm::date_t x = test_lmm::DiscountFactorTestData::dates()(index);
        const double expected 
            = test_lmm::DiscountFactorTestData::discountFactors()(index);
        ASSERT_DOUBLE_EQ(expected, interpolant(x));
    }
    {
        const std::size_t index = 4;
        const lmm::date_t x 
            = test_lmm::DiscountFactorTestData::dates()(index) 
                + boost::gregorian::date_duration(1);
        const double expected
            = test_lmm::DiscountFactorTestData::discountFactors()(index)
            + (test_lmm::DiscountFactorTestData::discountFactors()(index + 1)
                - test_lmm::DiscountFactorTestData::discountFactors()(index))
            / static_cast<double>((
                test_lmm::DiscountFactorTestData::dates()(index + 1)
                - test_lmm::DiscountFactorTestData::dates()(index)).days());
        ASSERT_DOUBLE_EQ(expected, interpolant(x));
    }
}
