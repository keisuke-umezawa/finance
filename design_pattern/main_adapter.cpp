#include <iostream>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "IOptimizeMethod.h"
#include "NewtonMethod.h"
#include "LevenbergMarquardtMethod.h"
#include "LeastSquareOptimizer.h"

namespace ublas = boost::numeric::ublas;

double hoge(double x, const ublas::vector<double>& parameters)
{
    return parameters(0) + parameters(1) * x + parameters(2) * x * x;
}

int main() 
{
    // data
    ublas::vector<double> abscissas(4, 0.0);
    abscissas(0) = 1.0; 
    abscissas(1) = 2.0;
    abscissas(2) = 3.0;
    abscissas(3) = 4.0;
    ublas::vector<double> ordinates(4, 0.0);
    ordinates(0) = 1.0; 
    ordinates(1) = 4.0;
    ordinates(2) = 9.0;
    ordinates(3) = 16.0;

    {
        const boost::shared_ptr<design_pattern::IOptimizeMethod> method
            = boost::make_shared<design_pattern::NewtonMethod>(10000, 1e-10);
        const design_pattern::LeastSquareOptimizer 
            optimizer(method, abscissas, ordinates);

        const ublas::vector<double> optimizedParameter
            = optimizer.optimize(hoge, ublas::vector<double>(3, 0.0));
        std::cout << optimizedParameter << std::endl;

        for (std::size_t i = 0; i < abscissas.size(); ++i) {
            std::cout << "answer : " << ordinates(i) << std::endl;
            std::cout << "result ; " << 
                hoge(abscissas(i), optimizedParameter) << std::endl;
        }

    }

    {
        const boost::shared_ptr<design_pattern::IOptimizeMethod> method
            = boost::make_shared<
                design_pattern::LevenbergMarquardtMethod>(1e-10);
        const design_pattern::LeastSquareOptimizer 
            optimizer(method, abscissas, ordinates);

        const ublas::vector<double> optimizedParameter
            = optimizer.optimize(hoge, ublas::vector<double>(3, 0.0));
        std::cout << optimizedParameter << std::endl;

        for (std::size_t i = 0; i < abscissas.size(); ++i) {
            std::cout << "answer : " << ordinates(i) << std::endl;
            std::cout << "result ; " << 
                hoge(abscissas(i), optimizedParameter) << std::endl;
        }

    }
    return 0;
}