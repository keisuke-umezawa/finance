#include "gmock/gmock.h"    //<label id="code.include"/>
#include "IStochasticProcess.h"

using namespace testing;

class StochasticProcessTest : public testing::Test {
public:
};

TEST_F(StochasticProcessTest, testLogNormalSdeDrift) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type initialDate(2014, 2, 3);
    const double initialValue = 100.0;
    const finance::NormalProcess process(mu, sigma);
    const double state = 2.0;
    const finance::date_type date(2014, 2, 4);

    ASSERT_THAT(finance::mean(process, date), Eq(mu / 365.0));
}

