#ifndef LEASTSQUAREOPTIMIZER_H_INCLUDED
#define LEASTSQUAREOPTIMIZER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "fwd.h"
#include "numeric.h"
#include "OptimizeTargetFunctor.h"

namespace design_pattern {
    class LeastSquareOptimizer {
    public:
        LeastSquareOptimizer(
            const boost::shared_ptr<IOptimizeMethod>& method,
            const ublas::vector<double>& abscissas, 
            const ublas::vector<double>& ordinates)
        : _method(method), _abscissas(abscissas), _ordinates(ordinates)
        {
        }

        ublas::vector<double> optimize(
            const boost::function<double(double, ublas::vector<double>)>& 
                function,
            const ublas::vector<double>& initialParameters) const
        {
            const OptimizeTargetFunctor target 
                = makeOptimizeTargetFunctor(function, _abscissas, _ordinates);
            return _method->optimize(target, initialParameters);
        }

    private:
        const boost::shared_ptr<const IOptimizeMethod> _method;
        const ublas::vector<double> _abscissas;
        const ublas::vector<double> _ordinates;
    };
}  // namespace design_pattern

#endif // LEASTSQUAREOPTIMIZER_H_INCLUDED
