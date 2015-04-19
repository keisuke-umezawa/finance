#include "gmock/gmock.h"    //<label id="code.include"/>
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
class TmpTest : public testing::Test {
public:
};


TEST_F(TmpTest, testTmp) {
}
