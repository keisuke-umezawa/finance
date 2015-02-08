#include "gmock/gmock.h"    //<label id="code.include"/>
#include "ISde.h"
#include "IShortRate.h"


using namespace testing;

class SdeTest : public testing::Test {
public:
};

TEST_F(SdeTest, testLogNormalSdeDrift) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::LogNormalSde sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.drift(date, state), Eq(mu * state));
}

TEST_F(SdeTest, testLogNormalSdeDiffusion) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::LogNormalSde sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.diffusion(date, state), Eq(sigma * state));
}

TEST_F(SdeTest, testNormalSdeDrift) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::NormalSde sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.drift(date, state), Eq(mu));
}

TEST_F(SdeTest, testNormalSdeDiffusion) {
    const double mu = 0.2;
    const double sigma = 0.1;
    const finance::date_type date(2014, 2, 3);
    const finance::NormalSde sde(mu, sigma);
    const double state = 2.0;

    ASSERT_THAT(sde.diffusion(date, state), Eq(sigma));
}
