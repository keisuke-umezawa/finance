#ifndef NEWTONMETHOD_H_INCLUDED
#define NEWTONMETHOD_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include "fwd.h"
#include "numeric.h"

namespace design_pattern {

    class NewtonMethod :
        public IOptimizeMethod, private boost::noncopyable {
    public:
        NewtonMethod(const std::size_t maxIteration, const double tolerance)
        : _maxIteration(maxIteration), _tolerance(tolerance)
        {
        }
    private:
        virtual ublas::vector<double> doOptimize(
            const OptimizeTargetFunctor& target,
            const ublas::vector<double>& initials) const
        {
            return numeric::newton(target, initials, 
                _maxIteration, _tolerance);
        }

        const std::size_t _maxIteration;
        const double _tolerance;
    };
}  // namespace design_pattern

#endif // NEWTONMETHOD_H_INCLUDED
