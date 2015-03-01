#include "gmock/gmock.h"    //<label id="code.include"/>
#include "Polynomial.h"
#include "Jacobian.h"

using namespace testing;
namespace ublas = boost::numeric::ublas;

class JacobianTest : public testing::Test {
public:
};

TEST_F(JacobianTest, testJacobianWithVector) {
    BOOST_AUTO(calibratingFunction, 
        finance::auto_diff::makeCalibratingPolynomial<3>(0.0));
    ublas::vector<double> coefficients(3, 0.0);
    coefficients(0) = 1.0;
    coefficients(1) = -2.0;
    coefficients(2) = 1.0;

    finance::auto_diff::jacobian(calibratingFunction, coefficients);
    //ASSERT_THAT(calibratingFunction(coefficients), Eq(1.0));
}
