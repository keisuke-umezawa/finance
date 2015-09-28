#ifndef LEVENBERGMARQUARDTMETHOD_H_INCLUDED
#define LEVENBERGMARQUARDTMETHOD_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <dlib/optimization.h>
#include "fwd.h"
#include "numeric.h"
#include "OptimizeTargetFunctor.h"
#include "IOptimizeMethod.h"

namespace design_pattern {
    class LevenbergMarquardtMethod : 
        public IOptimizeMethod, private boost::noncopyable {
    private:
        typedef dlib::matrix<double, 0, 1> column_vector;
    public:
        LevenbergMarquardtMethod(const double tolerance)
        : _tolerance(tolerance)
        {
        }

    private:
        virtual ublas::vector<double> doOptimize(
            const OptimizeTargetFunctor& target,
            const ublas::vector<double>& initials) const;

        const double _tolerance;
    };
}  // namespace design_pattern

#endif // LEVENBERGMARQUARDTMETHOD_H_INCLUDED
