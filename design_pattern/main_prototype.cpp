#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"
#include "Interpolant.h"
#include "InterpolantDecorator.h"
#include "InterpolantPrototypeFactory.h"
#include "YieldCurve.h"


int main()
{
    namespace ublas = boost::numeric::ublas;

    ublas::vector<double> abscissas(5, 0.0);
    abscissas(0) = 1.0;
    abscissas(1) = 2.0;
    abscissas(2) = 3.0;
    abscissas(3) = 4.0;
    abscissas(4) = 5.0;

    ublas::vector<double> ordinates(5, 0.0);
    ordinates(0) = 2.0;
    ordinates(1) = 4.0;
    ordinates(2) = 6.0;
    ordinates(3) = 8.0;
    ordinates(4) = 10.0;

    const design_pattern::LinearInterpolant linerInterpolant;

    const design_pattern::InterpolantPrototypeFactory
        linearInterpolantFactory(linerInterpolant);

    const design_pattern::InterpolantPrototypeFactory 
        logLinearInterpolantFactory 
            = design_pattern::log(linearInterpolantFactory);

    {
        const design_pattern::YieldCurve yieldCurve(logLinearInterpolantFactory);
        std::cout << yieldCurve(-1.0) << std::endl;
        std::cout << yieldCurve(3.0) << std::endl;
        std::cout << yieldCurve(3.5) << std::endl;
        std::cout << yieldCurve(10.0) << std::endl;
    }

    return 0;
}