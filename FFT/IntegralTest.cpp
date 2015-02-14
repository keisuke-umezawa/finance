#include "gmock/gmock.h"    //<label id="code.include"/>
#include "IDeterministicProcess.h"
#include "Integral.h"
#include "tmp.h"
#include <boost/bind.hpp>

using namespace testing;

namespace {
    template <typename T>
    T f(const T& x)
    {
        return x * x;
    }
}
class IntegralTest : public testing::Test {
public:
};

TEST_F(IntegralTest, testIntegralConstantProcess) {
    const double constant = 0.2;
    const finance::date_type t0(2014, 2, 3);
    const finance::date_type t1(2014, 2, 4);
    const finance::ConstantProcess process(constant);

    ASSERT_THAT(finance::integral(process, t0, t1), Eq(0.2 / 365.0));
}

TEST_F(IntegralTest, testTmp) {
    std::cout << finance::get(boost::bind(&f<double>(), _1), 1.0) << std::endl; 
}
