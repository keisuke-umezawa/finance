/*
 * SabrPricer.h
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#ifndef SABRPRICER_H_INCLUDED
#define SABRPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "SabrModelParameter.h"
#include "MarketDataSet.h"
#include "YieldCurve.h"

namespace design_pattern {

    class SabrPricer {
    public:
        SabrPricer::SabrPricer(const SabrModelParameter& parameter,
            const YieldCurve& yieldCurve);

        const double calculatePrice(const double spot, const double maturity,
            const double strike) const;

        void SabrPricer::setParameter(const SabrModelParameter& parameter,
            const YieldCurve& yieldCurve);

        boost::shared_ptr<SabrPricer> clone() const;

    private:
        SabrPricer(const SabrPricer& other);
        SabrPricer& operator =(const SabrPricer& other);
    private:
        SabrModelParameter _parameter;
        boost::shared_ptr<const YieldCurve> _yieldCurve;
    };

}  // namespace design_pattern

#endif // SABRPRICER_H_INCLUDED
