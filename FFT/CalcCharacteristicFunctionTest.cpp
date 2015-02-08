#include "gmock/gmock.h"    //<label id="code.include"/>
#include "ISde.h"
#include "CalcCharacteristicFunction.h"


using namespace testing;

class CalcCharacteristicFunctionTest : public testing::Test {
public:
};

TEST_F(CalcCharacteristicFunctionTest, testDrift) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::BsModel sde(mu, sigma);
    const double wave = 2.0;

    finance::calcCharacteristicFunction(wave, sde);

    //ASSERT_THAT(sde.drift(date, state), Eq(mu * state));
}

