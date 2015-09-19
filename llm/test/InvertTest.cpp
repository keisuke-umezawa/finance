/*
 * InvertTest.cpp
 *
 *  Created on: 2015/06/01
 *      Author: Keisuke
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "../src/fwd.h"
#include "../src/invert.h"

TEST(InvertTest, invert) {
    const ublas::matrix<double> m(ublas::identity_matrix<double>(4));
    EXPECT_NEAR(m(0, 0), 1.0, 1e-5);
    EXPECT_NEAR(m(1, 1), 1.0, 1e-5);
    EXPECT_NEAR(m(2, 2), 1.0, 1e-5);
    ASSERT_NEAR(m(3, 3), 1.0, 1e-5);
}
