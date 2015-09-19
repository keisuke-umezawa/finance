/*
 * PiecewiseConstantLiborMarketModel.cpp
 *
 *  Created on: 2015/06/24
 *      Author: Keisuke
 */


#include "fwd.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "DayCountFraction.h"

namespace lmm {

    ublas::matrix<double> calcPiecewiseConstantVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::vector<double>& capletVolatilites)
    {
        ublas::matrix<double> piecewiseConstantVolatilities(
            capletVolatilites.size(), capletVolatilites.size(), 0.0);
        for (std::size_t i = 0; i < capletVolatilites.size(); ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                piecewiseConstantVolatilities(i, j + 1)
                    = piecewiseConstantVolatilities(i - 1, j);
            }
            double integralOfPiecewiseConstantVolatilities = 0.0;
            for (std::size_t j = 1; j <= i; ++j) {
                integralOfPiecewiseConstantVolatilities
                    += std::pow(piecewiseConstantVolatilities(i, j), 2)
                        * dayCountAct365(
                            (j == 0 ? today : dates(j - 1)),
                            dates(j));
            }
            double integralOfCapletVolatilities
                = std::pow(capletVolatilites(i), 2)
                    * dayCountAct365(today, dates(i));
            if (integralOfCapletVolatilities
                    - integralOfPiecewiseConstantVolatilities < 0) {
                piecewiseConstantVolatilities(i, 0) = 0.0;
            }
            else {
                piecewiseConstantVolatilities(i, 0)
                    = std::sqrt(
                        (integralOfCapletVolatilities
                            - integralOfPiecewiseConstantVolatilities)
                            / dayCountAct365((i == 0 ? today : dates(i - 1)),
                                dates(i)));
            }
        }
        return piecewiseConstantVolatilities;
    }

    std::vector<ublas::matrix<double> > calcDiscountFactorChangeRatios(
        const ublas::vector<double>& discountFactors,
        const std::size_t maxSwaptionMaturityIndex,
        const std::size_t maxSwaptionUnderlyingIndex)
    {
        std::vector<ublas::matrix<double> > changeRatios(
            maxSwaptionUnderlyingIndex);
        for (std::size_t i = 0; i < maxSwaptionUnderlyingIndex; ++i) {
            ublas::matrix<double> ratio(
                maxSwaptionMaturityIndex, maxSwaptionUnderlyingIndex, 0.0);
            for (std::size_t j = i + 1; j <= maxSwaptionMaturityIndex + i; ++j) {
                for (std::size_t k = i + 1; k <= j; ++k) {
                    ratio(j - i - 1, k - i - 1) = (discountFactors(k - 1) - discountFactors(k))
                        / (discountFactors(i) - discountFactors(j));
                }
            }
            changeRatios[i] = ratio;
        }
        return changeRatios;
    }
    ublas::matrix<double> calcLiborCovariance(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const ublas::matrix<double>& swaptionVolatilities,
        const std::vector<ublas::matrix<double> >& changeRatios)
    {
        ublas::matrix<double> covariance(
            changeRatios.size(), changeRatios.size());
        for (std::size_t i = 0; i < covariance.size1(); ++i) {
            covariance(i, i) = std::pow(swaptionVolatilities(i, 0), 2);
        }

        double sumBuffer = 0.0;
        for (std::size_t i = 0; i < covariance.size1(); ++i) {
            for (std::size_t j = i + 1; j < covariance.size1(); ++j) {
                double sum = 0.0;
                for (std::size_t l = i + 1; l < j + 1; ++l) {
                    for (std::size_t k = i + 1; k < j + 1; ++k) {
                        sumBuffer = changeRatios[i](j - i, k - 1 - i)
                            * changeRatios[i](j - i, l - 1 - i)
                            * covariance(k - 1, l - 1);
                        sum += sumBuffer;
                    }
                }
                covariance(i, j) = (std::pow(swaptionVolatilities(i, j - i), 2) - sum)
                    / (4.0 * changeRatios[i](j - i, 0)
                       * changeRatios[i](j - i, j - i));
                covariance(j, i) = covariance(i, j);
            }
        }
        return covariance;
    }
}  // namespace lmm


