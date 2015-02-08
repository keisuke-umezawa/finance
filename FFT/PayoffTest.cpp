#include "gmock/gmock.h"    //<label id="code.include"/>
#include "IShortRate.h"
#include "IPayoff.h"

using namespace testing;

class PayoffTest : public testing::Test {
public:
};

TEST_F(PayoffTest, testCallPayoff) {
    const double strike = 100.0;
    finance::CallPayoff payoff(strike);

    ASSERT_THAT(payoff(110.0), Eq(10.0));
}

