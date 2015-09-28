/*
 * SabrCalibrator.h
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#ifndef SABRCALIBRATOR_H_INCLUDED
#define SABRCALIBRATOR_H_INCLUDED

#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include "MarketDataSet.h"
#include "SabrModelParameter.h"
#include "MarketDataSet.h"

namespace design_pattern {

    class SabrCalibrator {
    public:
        SabrCalibrator(
            const SabrModelParameter& initialParameter, const double beta,
            const double tolerance, const std::size_t maxIteration);

        const SabrModelParameter& calibrate(
            const VolatilityDataSet& volatilityData);

        boost::shared_ptr<SabrCalibrator> clone() const;

    private:
        SabrModelParameter _parameter;
        const double _beta;
        const double _tolerance;
        const std::size_t _maxIteration;
    };

}  // namespace design_pattern

#endif // SABRCALIBRATOR_H_INCLUDED
