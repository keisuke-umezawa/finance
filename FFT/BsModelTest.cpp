#include "gmock/gmock.h"    //<label id="code.include"/>
#include "ISde.h"
#include "IShortRate.h"


using namespace testing;

class BSModelTest : public testing::Test {
public:
};

TEST_F(BSModelTest, testDrift) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::BsModel sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.drift(date, state), Eq(mu * state));
}

TEST_F(BSModelTest, testDiffusion) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::BsModel sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.diffusion(date, state), Eq(sigma * state));
}
