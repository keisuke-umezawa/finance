#include "gmock/gmock.h"    //<label id="code.include"/>
#include "IOption.h"


using namespace testing;

class OptionTest : public testing::Test {
public:
};

TEST_F(OptionTest, testOptionPayoff) {
    const double strike = 100.0;
    const finance::CallPayoff payoff(strike);
    const finance::date_type date(2014, 2, 3);
    const finance::EuropeanOption option(payoff, date); 

    ASSERT_THAT(option.payoff(110.0), Eq(10.0));
}

TEST_F(OptionTest, testOptionExpiry) {
    const double strike = 100.0;
    const finance::CallPayoff payoff(strike);
    const finance::date_type date(2014, 2, 3);
    const finance::EuropeanOption option(payoff, date); 

    ASSERT_THAT(option.expiryDate(), Eq(date));
}
