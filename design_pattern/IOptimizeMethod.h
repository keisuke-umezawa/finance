#ifndef IOPTIMIZEMETHOD_H_INCLUDED
#define IOPTIMIZEMETHOD_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "OptimizeTargetFunctor.h"

namespace design_pattern {
    namespace ublas = boost::numeric::ublas;

    class IOptimizeMethod {
    public:
        ublas::vector<double> optimize(
            const OptimizeTargetFunctor& target,
            const ublas::vector<double>& initials) const
        {
            return doOptimize(target, initials);
        }

    private:
        virtual ublas::vector<double> doOptimize(
            const OptimizeTargetFunctor& target,
            const ublas::vector<double>& initials) const = 0;
    };
}  // namespace design_pattern

#endif // IOPTIMIZEMETHOD_H_INCLUDED
