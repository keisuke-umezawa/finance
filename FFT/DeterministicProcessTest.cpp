#include "gmock/gmock.h"    //<label id="code.include"/>
#include "IProcess.h"

using namespace testing;

class DeterministicProcessTest : public testing::Test {
public:
};

TEST_F(DeterministicProcessTest, testConstantShortRate) {
    const finance::date_type date(2014, 2, 3);
    const finance::ConstantShortRate rate(3.0);

    ASSERT_THAT(rate(date), Eq(3.0));
}

