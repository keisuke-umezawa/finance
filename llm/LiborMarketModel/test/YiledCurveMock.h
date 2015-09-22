#include <gmock/gmock.h>
#include "fwd.h"
#include "YieldCurve.h"


namespace test_lmm {
    class YieldCurveMock : public lmm::IYieldCurve {
    public:
        MOCK_CONST_METHOD2(doDiscountFactor,
            const double(const lmm::date_t& start, const lmm::date_t& end));
        MOCK_CONST_METHOD0(doClone, lmm::IYieldCurve*());

    public:
        lmm::IYieldCurve* delegateDoClone() const
        {
            return new YieldCurveMock();
        }
    };

} // namespace test_lmm {