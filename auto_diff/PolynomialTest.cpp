#include "gmock/gmock.h"    //<label id="code.include"/>
#include "Polynomial.h"
#include "Dual.h"
#include "DualFunction.h"

using namespace testing;
namespace ublas = boost::numeric::ublas;

class PolynomialTest : public testing::Test {
public:
};

TEST_F(PolynomialTest, testMakePolynomial) {
    ublas::vector<double> coefficients(3, 0.0);
    coefficients(0) = 1.0;
    coefficients(1) = 2.0;
    coefficients(2) = 1.0;
    BOOST_AUTO(const f, finance::auto_diff::makePolynomial<3>(coefficients));
    ASSERT_THAT(f(0.0), Eq(1.0));
    ASSERT_THAT(f(-1.0), Eq(0.0));
}

TEST_F(PolynomialTest, testDegree) {
    ublas::vector<double> coefficients(3, 0.0);
    coefficients(0) = 1.0;
    coefficients(1) = 2.0;
    coefficients(2) = 1.0;
    BOOST_AUTO(const f, finance::auto_diff::makePolynomial<3>(coefficients));
    ASSERT_THAT(f.degree(), Eq(3U));
}

TEST_F(PolynomialTest, testSetCoeffieicients) {
    ublas::vector<double> coefficients(3, 0.0);
    coefficients(0) = 1.0;
    coefficients(1) = 2.0;
    coefficients(2) = 1.0;
    BOOST_AUTO(f, finance::auto_diff::makePolynomial<3>(coefficients));
    coefficients(0) = 1.0;
    coefficients(1) = -2.0;
    coefficients(2) = 1.0;
    f.setCoefficients(coefficients);
    ASSERT_THAT(f(0.0), Eq(1.0));
    ASSERT_THAT(f(1.0), Eq(0.0));
}

TEST_F(PolynomialTest, testMakeCalibratingPolynomial) {
    BOOST_AUTO(calibratingFunction, 
        finance::auto_diff::makeCalibratingPolynomial<3>(0.0));
    ublas::vector<double> coefficients(3, 0.0);
    coefficients(0) = 1.0;
    coefficients(1) = -2.0;
    coefficients(2) = 1.0;
    ASSERT_THAT(calibratingFunction(coefficients), Eq(1.0));
}

TEST_F(PolynomialTest, testMakePolynomialWithDual) {
    typedef finance::auto_diff::Dual<double, ublas::c_vector<double, 3> > Dual;
    ublas::vector<Dual> coefficients(3, 0.0);
    coefficients(0) = finance::auto_diff::makeDual<3>(1.0, 1.0);
    coefficients(1) = finance::auto_diff::makeDual<3>(2.0, 1.0);
    coefficients(2) = finance::auto_diff::makeDual<3>(1.0, 1.0);
    BOOST_AUTO(const f, finance::auto_diff::makePolynomial<3>(coefficients));
    ASSERT_THAT(f(0.0), Eq(1.0));
    ASSERT_THAT(f(-1.0), Eq(0.0));
}
