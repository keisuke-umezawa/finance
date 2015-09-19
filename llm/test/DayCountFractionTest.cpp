#include <gtest/gtest.h>
#include "../src/fwd.h"
#include "../src/DayCountFraction.h"

TEST(DayCountFractionTest, testDayCountAct365) {
    const lmm::date_t start(2014, 2, 3);
    const lmm::date_t end(2014, 2, 4);

    ASSERT_DOUBLE_EQ(lmm::dayCountAct365(start, end), 1.0 / 365.0);
}
