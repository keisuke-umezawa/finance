#ifndef OPTIMIZETARGETFUNCTOR_H_INCLUDED
#define OPTIMIZETARGETFUNCTOR_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"

namespace design_pattern {

    class OptimizeTargetFunctor {
    public:
        typedef double result_type;

        OptimizeTargetFunctor(
            const boost::function<double(double, ublas::vector<double>)>& 
                function,
            const ublas::vector<double>& abscissas,
            const ublas::vector<double>& ordinates)
        : _function(function), _abscissas(abscissas), _ordinates(ordinates)
        {
        }
        
        const result_type operator()(
            const ublas::vector<double>& parameters) const;

    private:
        boost::function<double(double, ublas::vector<double>)> _function;
        ublas::vector<double> _abscissas;
        ublas::vector<double> _ordinates;
    };

    OptimizeTargetFunctor makeOptimizeTargetFunctor(
        const boost::function<double(double, ublas::vector<double>)>& function,
        const ublas::vector<double>& abscissas,
        const ublas::vector<double>& ordinates);
}  // namespace design_pattern

#endif // OPTIMIZETARGETFUNCTOR_H_INCLUDED
