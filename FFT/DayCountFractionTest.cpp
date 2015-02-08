#include "gmock/gmock.h"    //<label id="code.include"/>
#include "DayCountFraction.h"

using namespace testing;

class DayCountFractionTest : public testing::Test {
public:
};

TEST_F(DayCountFractionTest, testDayCountAct365) {
    const finance::date_type start(2014, 2, 3);
    const finance::date_type end(2014, 2, 4);

    ASSERT_THAT(finance::dayCountAct365(start, end), Eq(1.0 / 365.0));
}
