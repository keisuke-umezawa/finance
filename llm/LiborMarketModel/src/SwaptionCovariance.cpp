
#include <boost/function.hpp>
#include "fwd.h"
#include "DayCountFraction.h"
#include "SwaptionCovariance.h"
#include "Tenor.h"

namespace lmm {
    const double calculateDiagonalElement(
        const double swaptionVolatility,
        const date_t& today,
        const Tenor& tenor,
        const boost::function<double(date_t)>& lambda)
    {
        const date_t tenorDate = addTenor(today, tenor);
        return dayCountAct360(today, tenorDate)
            * swaptionVolatility * swaptionVolatility
            / lambda(tenorDate);
    }
    const double calculateNonDiagonalElement(
        const double swaptionVolatility,
        const DiscountFactorRatioGenerator& generator,
        const date_t& today,
        const Tenor& tenor,
        const boost::function<double(date_t)>& lambda)
    {
        return 0.0;
    }
    ublas::matrix<double> calculateSwaptionCovariance(
        const ublas::matrix<double>& swaptionVolatilities,
        const DiscountFactorRatioGenerator& generator,
        const date_t& today,
        const ublas::vector<Tenor>& tenors,
        const boost::function<double(date_t)>& lambda)
    {
        ublas::matrix<double> covariance(
            tenors.size(), tenors.size(), 0.0);
        for (std::size_t i = 0; i < tenors.size(); ++i) {
            const Tenor& start = tenors(i);
            covariance(i, i) = calculateDiagonalElement(
                swaptionVolatilities(i, 0), today, start, lambda);
        }

        double sumBuffer = 0.0;
        for (std::size_t i = 0; i < covariance.size1(); ++i) {
            for (std::size_t j = i + 1; j < covariance.size1(); ++j) {
                double sum = 0.0;
                for (std::size_t l = i + 1; l < j + 1; ++l) {
                    for (std::size_t k = i + 1; k < j + 1; ++k) {
                        sumBuffer = generator.get(tenors(i), tenors(j))(k - 1)
                            * generator.get(tenors(i), tenors(j))(l - 1)
                            * covariance(k - 1, l - 1);
                        sum += sumBuffer;
                    }
                }
                covariance(i, j) = (std::pow(swaptionVolatilities(i, j - i), 2) - sum)
                    / (4.0 * generator.get(tenors(i), tenors(j))(0)
                        * generator.get(tenors(i), tenors(j))(j));
                covariance(j, i) = covariance(i, j);
            }
        }
        return covariance;
    }
}  // namespace lmm
