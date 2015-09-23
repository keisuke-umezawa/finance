#include "fwd.h"
#include "YieldCurve.h"
#include "DayCountFraction.h"

namespace lmm {
    const double forwardRate(const IYieldCurve& yieldCurve,
        const date_t& today, const date_t& start, const date_t& end)
    {
        return (yieldCurve.discountFactor(today, start) 
                / yieldCurve.discountFactor(today, end) - 1.0)
            / dayCountAct360(start, end);
    }
} // namespace lmm {
