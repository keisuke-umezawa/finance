/*
 * PiecewiseConstantLiborMarketModel.h
 *
 *  Created on: 2015/06/24
 *      Author: Keisuke
 */

#ifndef PIECEWISECONSTANTLIBORMARKETMODELTEST_H_INCLUDED
#define PIECEWISECONSTANTLIBORMARKETMODELTEST_H_INCLUDED

#include "fwd.h"

namespace lmm {

    ublas::matrix<double> calcPiecewiseConstantVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& capletVolatilites);

    std::vector<ublas::matrix<double> > calcDiscountFactorChangeRatios(
        const ublas::vector<double>& discountFactors,
        const std::size_t maxSwaptionMaturityIndex,
        const std::size_t maxSwaptionUnderlyingIndex);

    ublas::matrix<double> calcLiborCovariance(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::matrix<double>& swaptionVolatilities,
        const std::vector<ublas::matrix<double> >& changeRatios);
}  // namespace lmm




#endif // PIECEWISECONSTANTLIBORMARKETMODELTEST_H_INCLUDED
