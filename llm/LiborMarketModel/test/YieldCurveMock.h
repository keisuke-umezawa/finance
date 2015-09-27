#include <gmock/gmock.h>
#include "fwd.h"
#include "YieldCurve.h"
#include "Tenor.h"
#include "DayCountFraction.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

namespace test_lmm {
    inline double returnZeroOver6Months(
        const lmm::date_t& start, const lmm::date_t& end)
    {
        if (end > lmm::addMonths(start, 6)) {
            return 0.0;
        }
        if (end > lmm::addMonths(start, 3)) {
            return 0.5;
        }
        return 1.0;
    }
    inline double returnConstantDiscountFactor(
        const lmm::date_t& start, const lmm::date_t& end)
    {
        return std::exp(-0.01 * lmm::dayCountAct360(start, end));
    }

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