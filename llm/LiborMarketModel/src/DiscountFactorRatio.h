#ifndef DISCOUNTFACTORCHANGERATIO_H_INCLUDED
#define DISCOUNTFACTORCHANGERATIO_H_INCLUDED

#include <algorithm>
#include "fwd.h"
#include <boost/numeric/ublas/triangular.hpp>
#include "YieldCurve.h"
#include "Tenor.h"
#include "linalg/vector_proxy.h"

namespace lmm {
    class DiscountFactorRatioGenerator {
    public:
        DiscountFactorRatioGenerator(
            const IYieldCurve& yieldCurve,
            const date_t& today,
            const ublas::vector<Tenor>& startTenors,
            const ublas::vector<Tenor>& periodTenors);

        ublas::vector<double> get(const Tenor& start,
            const Tenor& period) const;

    private:
        ublas::matrix<ublas::vector<double> > _ratios;
        const ublas::vector<Tenor> _startTenors;
        const ublas::vector<Tenor> _periodTenors;
    };

    ublas::vector<double> makeDiscountFactorRatios(
        const IYieldCurve& yieldCurve,
        const date_t& today,
        const Tenor& startTenor,
        const ublas::vector<Tenor>& periodTernos);
}  // namespace lmm

#endif // DISCOUNTFACTORCHANGERATIO_H_INCLUDED
