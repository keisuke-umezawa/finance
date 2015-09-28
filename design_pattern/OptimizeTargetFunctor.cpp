#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "OptimizeTargetFunctor.h"

namespace design_pattern {

    const OptimizeTargetFunctor::result_type 
    OptimizeTargetFunctor::operator()(
        const ublas::vector<double>& parameters) const
    {
        double sum = 0;
        for (std::size_t i = 0; i < _abscissas.size(); ++i) {
            sum += std::pow(
                _function(_abscissas(i), parameters) - _ordinates(i), 2);
        }
        return sum;
    }

    OptimizeTargetFunctor makeOptimizeTargetFunctor(
        const boost::function<double(double, ublas::vector<double>)>& function,
        const ublas::vector<double>& abscissas,
        const ublas::vector<double>& ordinates)
    {
        return OptimizeTargetFunctor(function, abscissas, ordinates);
    }
}  // namespace design_pattern

