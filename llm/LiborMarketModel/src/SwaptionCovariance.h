#ifndef SWAPTIONCOVARIANCE_H_INCLUDED
#define SWAPTIONCOVARIANCE_H_INCLUDED

#include "fwd.h"
#include "DiscountFactorRatio.h"
#include <boost/function.hpp>

namespace lmm {
    const double calculateDiagonalElement(
        const double swaptionVolatility,
        const date_t& today,
        const Tenor& tenor,
        const boost::function<double(date_t)>& lambda);

    const double calculateNonDiagonalElement(
        const double swaptionVolatility,
        const DiscountFactorRatioGenerator& generator,
        const date_t& today,
        const Tenor& tenor,
        const boost::function<double(date_t)>& lambda);

    ublas::matrix<double> calculateSwaptionCovariance(
        const ublas::matrix<double>& swaptionVolatilities,
        const DiscountFactorRatioGenerator& generator,
        const date_t& today,
        const ublas::vector<Tenor>& tenors,
        const boost::function<double(date_t)>& lambda);
}  // namespace lmm

#endif // SWAPTIONCOVARIANCE_H_INCLUDED
