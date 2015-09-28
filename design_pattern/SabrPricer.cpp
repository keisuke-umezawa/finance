/*
 * SabrPricer.cpp
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "SabrPricer.h"
#include "YieldCurve.h"
#include "SabrModelParameter.h"

namespace design_pattern {

    SabrPricer::SabrPricer(const SabrModelParameter& parameter,
        const YieldCurve& yieldCurve)
    : _parameter(parameter), _yieldCurve(yieldCurve.clone())
    {
    }

    SabrPricer::SabrPricer(const SabrPricer& other)
    : _parameter(other._parameter), _yieldCurve(other._yieldCurve->clone())
    {
    }

    const double SabrPricer::calculatePrice(
        const double spot, const double maturity, const double strike) const
    {
        return 1.0;
    }

    void SabrPricer::setParameter(const SabrModelParameter& parameter,
        const YieldCurve& yieldCurve)
    {
        _parameter = parameter;
        _yieldCurve = yieldCurve.clone();
    }

    boost::shared_ptr<SabrPricer> SabrPricer::clone() const
    {
        return boost::shared_ptr<SabrPricer>(
            new SabrPricer(*this));
    }

}  // namespace design_pattern
