#ifndef NUMERIC_H_INCLUDED
#define NUMERIC_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "invert.h"

namespace numeric {
    template <typename E> inline
    ublas::vector<double> derivative(
        const boost::function<double(ublas::vector<double>)>& f,
        const ublas::vector_expression<E>& vec,
        const double delta)
    {
        ublas::vector<double> result(vec().size(), 0.0);
        for (std::size_t i = 0; i < vec().size(); ++i) {
            ublas::vector<double> delta_vec(vec().size(), 0.0);
            delta_vec(i) += delta;
            result(i) = (f(vec + delta_vec) - f(vec - delta_vec)) 
                / (2.0 * delta);
        }
        return result;
    }

    template <typename E> inline
    ublas::matrix<double> jacobi(
        const boost::function<double(ublas::vector<double>)>& function,
        const ublas::vector_expression<E>& vec,
        const double delta)
    {
        ublas::matrix<double> result(1, vec().size(), 0.0);
        ublas::noalias(ublas::row(result, 0)) 
            = derivative(function, vec, delta);
        return result;
    }

    template <typename E> inline
    ublas::vector<double> newton(
        const boost::function<double(ublas::vector<double>)>& function,
        const ublas::vector_expression<E>& initials,
        const std::size_t maxIteration,
        const double tolerance)
    {
        ublas::vector<double> current(initials());
        ublas::vector<double> previous(initials());
        for (std::size_t i = 0; i < maxIteration; ++i) {
            const ublas::matrix<double> jacobi_matrix(
                jacobi(function, current, 1e-10));
            current -= ublas::column(numeric::pseudo_invert(jacobi_matrix), 0)
                * function(current);
            if (ublas::norm_2(current - previous) < tolerance) {
                break;
            }
            previous = current;
        }
        return current;
    }

}  // namespace numeric



#endif // NUMERIC_H_INCLUDED
