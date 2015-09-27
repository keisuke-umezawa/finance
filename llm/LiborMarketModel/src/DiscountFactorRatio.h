#ifndef DISCOUNTFACTORCHANGERATIO_H_INCLUDED
#define DISCOUNTFACTORCHANGERATIO_H_INCLUDED

#include <algorithm>
#include "fwd.h"
#include <boost/numeric/ublas/triangular.hpp>
#include "YieldCurve.h"
#include "Tenor.h"
#include "linalg/vector_proxy.h"

namespace lmm {
    inline const std::size_t toIndex(
        const Tenor& tenor, const ublas::vector<Tenor> tenors)
    {
        return std::find(tenors.begin(), tenors.end(), tenor)
            - tenors.begin();
    }
    inline ublas::vector<double> makeDiscountFactorRatios(
        const IYieldCurve& yieldCurve,
        const date_t& today,
        const Tenor& startTenor,
        const ublas::vector<Tenor>& periodTernos)
    {
        ublas::vector<double> ratios(periodTernos.size());
        const date_t start = lmm::addTenor(today, startTenor);
        const date_t end = lmm::addTenor(start, *periodTernos.crbegin());

        const ublas::vector<Tenor> periods
            = linalg::add_front(periodTernos, Tenor());
        const double denominator
            = yieldCurve.discountFactor(today, start)
                - yieldCurve.discountFactor(today, end);
        for (std::size_t i = 0; i < ratios.size(); ++i) {
            ratios(i) = (yieldCurve.discountFactor(today,
                    lmm::addTenor(start, periods(i)))
                - yieldCurve.discountFactor(today,
                    lmm::addTenor(start, periods(i + 1))))
                / denominator;
        }
        return ratios;
    }
    class DiscountFactorRatioGenerator {
    public:
        DiscountFactorRatioGenerator(
            const IYieldCurve& yieldCurve,
            const date_t& today,
            const ublas::vector<Tenor>& startTenors,
            const ublas::vector<Tenor>& periodTenors)
        : _ratios(startTenors.size(), periodTenors.size()),
            _startTenors(startTenors), _periodTenors(periodTenors)
        {
            for (std::size_t i = 0; i < _ratios.size1(); ++i) {
                for (std::size_t j = 0; j < _ratios.size2(); ++j) {
                    _ratios(i, j) = makeDiscountFactorRatios(
                        yieldCurve, today, _startTenors(i),
                        ublas::subrange(_periodTenors, 0, j + 1));
                }
            }
        }
        ublas::vector<double> get(
            const Tenor& start,
            const Tenor& period) const 
        {
            return _ratios(
                toIndex(start, _startTenors),
                toIndex(period, _periodTenors));
        }

    private:
        ublas::matrix<ublas::vector<double> > _ratios;
        const ublas::vector<Tenor> _startTenors;
        const ublas::vector<Tenor> _periodTenors;
    };
}  // namespace lmm

#endif // DISCOUNTFACTORCHANGERATIO_H_INCLUDED
