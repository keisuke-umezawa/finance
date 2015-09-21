#include "YieldCurve.h"

namespace lmm {
    boost::shared_ptr<IYieldCurve> makeLinearYieldCurve(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& discountFactors)
    {
        ublas::vector<date_t> copyDates(dates);
        copyDates.insert_element(0, today);
        ublas::vector<double> copyDfs(discountFactors);
        copyDfs.insert_element(0, 1.0);
        return boost::make_shared<PiecewiseYieldCurve>(
            LinearInterpolant(copyDates, copyDfs));
    }
} // namespace lmm {
