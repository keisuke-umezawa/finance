#ifndef YIELDCURVE_H_INCLUDED
#define YIELDCURVE_H_INCLUDED

#include "fwd.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"
#include "Interpolant.h"
#include "InterpolantPrototypeFactory.h"

namespace design_pattern {
    class YieldCurve {
    public:
        explicit YieldCurve(const InterpolantPrototypeFactory& factory) 
        : _interpolant(boost::make_shared<ConstantExtrapolationDecorator>(
            factory.create()))
        {
            // load data from file.
            ublas::vector<double> dates(5, 0.0);
            dates(0) = 1.0;
            dates(1) = 2.0;
            dates(2) = 3.0;
            dates(3) = 4.0;
            dates(4) = 5.0;

            ublas::vector<double> values(5, 0.0);
            values(0) = 2.0;
            values(1) = 4.0;
            values(2) = 6.0;
            values(3) = 8.0;
            values(4) = 10.0;

            _interpolant->init(values, values);
        }

        double operator()(const double date) const
        {
            return (*_interpolant)(date);
        }
    private:
        const boost::shared_ptr<Interpolant> _interpolant;
    };     
}

#endif // YIELDCURVE_H_INCLUDED