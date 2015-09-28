
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "numeric/numeric.h"

namespace numeric {

    double integral(const boost::function<double(double)>& f,
        const double start, const double end, const std::size_t divisionSize)
    {
        const double delta = (end - start) / static_cast<double>(divisionSize);
        double sum = 0.5 * f(start);
        for (std::size_t i = 1; i + 1 < divisionSize; ++i) {
            sum += f(start + static_cast<double>(i) * delta);
        }
        sum += 0.5 * f(end);
        sum *= delta;

        return sum;
    }

    double derivative(
        const boost::function<double(double)>& f,
        const double x,
        const double delta)
    {
        return (f(x + delta) - f(x - delta)) / (2.0 * delta);
    }

    double targetFunction(
        const boost::function<double(double)>& function,
        const double input,
        const double target)
    {
        return function(input) - target;
    }

    boost::function<double(double)> makeTargetFunction(
        const boost::function<double(double)>& function,
        const double target)
    {
        return boost::bind(targetFunction, function, _1, target);
    }
}  // namespace numeric


