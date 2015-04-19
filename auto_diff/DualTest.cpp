#include "gmock/gmock.h"    //<label id="code.include"/>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/typeof/typeof.hpp>
#include "Dual.h"
#include "DualFunction.h"

using namespace testing;
namespace ublas = boost::numeric::ublas;

class DualTest : public testing::Test {
public:
};

TEST_F(DualTest, testMakeDualWithReal) {
    BOOST_AUTO(const d, finance::auto_diff::makeDual<2>(2.0));
    ASSERT_THAT(d.real(), Eq(2.0));
    ASSERT_THAT(d.infinitesimal()(0), Eq(0.0));
    ASSERT_THAT(d.infinitesimal()(1), Eq(0.0));
}

TEST_F(DualTest, testMakeDualWithIndex) {
    BOOST_AUTO(const d, finance::auto_diff::makeDual<2>(2.0, 1));
    ASSERT_THAT(d.real(), Eq(2.0));
    ASSERT_THAT(d.infinitesimal()(0), Eq(0.0));
    ASSERT_THAT(d.infinitesimal()(1), Eq(1.0));
}

TEST_F(DualTest, testInfinitesimal1d) {
    BOOST_AUTO(const d, finance::auto_diff::makeDual<1>(2.0));
    ASSERT_THAT(d.real(), Eq(2.0));
    ASSERT_THAT(d.infinitesimal(), Eq(0.0));
}

TEST_F(DualTest, testConstructWithInfinitesimal) {
    typedef finance::auto_diff::Dual<double, ublas::c_vector<double, 2> > Dual;
    Dual d(2.0, ublas::unit_vector<double>(2, 1));
    ASSERT_THAT(d.real(), Eq(2.0));
    ASSERT_THAT(d.infinitesimal()(0), Eq(0.0));
    ASSERT_THAT(d.infinitesimal()(1), Eq(1.0));
}

TEST_F(DualTest, testDualDual) {
    BOOST_AUTO(const d, finance::auto_diff::makeDual<5>(2.0, 1));
    //BOOST_AUTO(const dd, finance::auto_diff::makeDual<5>(d, 2));
    //typedef finance::auto_diff::Dual<double, ublas::c_vector<double, 2> > Dual;
    //ublas::unit_vector<Dual> unitDual(3, 2);


    //DualDual dd;
    //BOOST_AUTO(const dd, finance::auto_diff::makeDual<3>(d));
    //ASSERT_THAT(d.real(), Eq(2.0));
    //ASSERT_THAT(d.infinitesimal(), Eq(0.0));
}
