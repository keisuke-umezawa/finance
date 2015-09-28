/*
 * SabrCalibrator.cpp
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#include <boost/make_shared.hpp>
#include "SabrCalibrator.h"
#include "SabrModelParameter.h"
#include "MarketDataSet.h"

namespace design_pattern {

        SabrCalibrator::SabrCalibrator(
            const SabrModelParameter& initialParameter, const double beta,
            const double tolerance, const std::size_t maxIteration)
        : _beta(beta), _parameter(initialParameter),
            _tolerance(tolerance), _maxIteration(maxIteration)
        {
        }

        const SabrModelParameter& SabrCalibrator::calibrate(
            const VolatilityDataSet& volatilityData)
        {
            // calibration
            _parameter.setAlpha(1.0);
            _parameter.setRho(1.0);
            _parameter.setNu(1.0);
            return _parameter;
        }

        boost::shared_ptr<SabrCalibrator> SabrCalibrator::clone() const
        {
            return boost::make_shared<SabrCalibrator>(*this);
        }

}  // namespace design_pattern
