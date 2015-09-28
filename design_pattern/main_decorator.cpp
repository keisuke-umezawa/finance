#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"
#include "Interpolant.h"
#include "InterpolantDecorator.h"

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

    {
        design_pattern::Interpolant& interpolant
            = design_pattern::LogInterpolantDecorator(
                design_pattern::LinearInterpolant().clone());

        interpolant.init(ordinates, abscissas);

        std::cout << interpolant(-1.0) << std::endl;
        std::cout << interpolant(3.0) << std::endl;
        std::cout << interpolant(3.5) << std::endl;
        std::cout << interpolant(10.0) << std::endl;
    }

    {
        design_pattern::Interpolant& interpolant
            = design_pattern::ConstantExtrapolationDecorator(
                design_pattern::LogInterpolantDecorator(
                    design_pattern::LinearInterpolant().clone()).clone());

        interpolant.init(ordinates, abscissas);

        std::cout << interpolant(-1.0) << std::endl;
        std::cout << interpolant(3.0) << std::endl;
        std::cout << interpolant(3.5) << std::endl;
        std::cout << interpolant(10.0) << std::endl;
    }

    {
        design_pattern::Interpolant& interpolant
            = design_pattern::MaxInterpolantDecorator(
                design_pattern::LinearInterpolant().clone(), 3.0);

        interpolant.init(ordinates, abscissas);

        std::cout << interpolant(-1.0) << std::endl;
        std::cout << interpolant(3.0) << std::endl;
        std::cout << interpolant(3.5) << std::endl;
        std::cout << interpolant(10.0) << std::endl;
    }

    return 0;
}