#include <gmock/gmock.h>
#include "fwd.h"
#include "Interpolant.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

namespace test_lmm {
    class InterpolantMock : public lmm::IInterpolant {
    public:
        MOCK_CONST_METHOD1(doOperator,
            const double(const lmm::date_t& x));
        MOCK_CONST_METHOD0(doClone, lmm::IInterpolant*());

    public:
        lmm::IInterpolant* delegateDoClone() const
        {
            return new InterpolantMock();
        }
    };

} // namespace test_lmm {