#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include <dlib/optimization.h>
#include "fwd.h"
#include "numeric.h"
#include "OptimizeTargetFunctor.h"
#include "LevenbergMarquardtMethod.h"

namespace {
    namespace ublas = boost::numeric::ublas;

    class OptimizeTargetFunctorWrapper {
    private:
        typedef dlib::matrix<double, 0, 1> column_vector;
    public:
        OptimizeTargetFunctorWrapper(
            const design_pattern::OptimizeTargetFunctor& target)
        : _target(target)
        {
        }

        double operator()(const column_vector& parameters) const 
        {
            ublas::vector<double> parameters_copy(parameters.size());
            for (std::size_t i = 0; i < parameters.size(); ++i) {
                parameters_copy(i) = parameters(i);
            }
            return _target(parameters_copy);
        }

    private:
        const design_pattern::OptimizeTargetFunctor _target;
    };

};

namespace design_pattern {

    ublas::vector<double> LevenbergMarquardtMethod::doOptimize(
        const OptimizeTargetFunctor& target,
        const ublas::vector<double>& initials) const
    {
        column_vector initials_copy(initials.size());
        for (std::size_t i = 0; i < initials.size(); ++i) {
            initials_copy(i) = initials(i);
        }
        dlib::find_min_using_approximate_derivatives(
            dlib::bfgs_search_strategy(),
            dlib::objective_delta_stop_strategy(_tolerance),
            OptimizeTargetFunctorWrapper(target), initials_copy, -1);

        ublas::vector<double> parameters(initials_copy.size());
        for (std::size_t i = 0; i < initials_copy.size(); ++i) {
            parameters(i) = initials_copy(i);
        }
        return parameters;
    }
}  // namespace design_pattern
