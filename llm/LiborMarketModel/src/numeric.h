/*
 * numeric.h
 *
 *  Created on: 2015/06/07
 *      Author: Keisuke
 */

#ifndef NUMERIC_H_INCLUDED
#define NUMERIC_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "invert.h"
#include "fwd.h"

namespace numeric {
    double integral(const boost::function<double(double)>& f,
        const double start, const double end, const std::size_t divisionSize);

    double derivative(
        const boost::function<double(double)>& f,
        const double x,
        const double delta);

    template <typename E> inline
    ublas::vector<double> derivative(
        const boost::function<double(double, double, double, double)>& f,
        const ublas::vector_expression<E>& vec,
        const double delta)
    {
        ublas::vector<double> result(4, 0.0);
        result(0) = derivative(boost::bind(f, _1, vec()(1), vec()(2), vec()(3)),
            vec()(0), delta);
        result(1) = derivative(boost::bind(f, vec()(0), _1, vec()(2), vec()(3)),
            vec()(1), delta);
        result(2) = derivative(boost::bind(f, vec()(0), vec()(1), _1, vec()(3)),
            vec()(2), delta);
        result(3) = derivative(boost::bind(f, vec()(0), vec()(1), vec()(2), _1),
            vec()(3), delta);
        return result;
    }

    template <typename E> inline
    ublas::matrix<double> jacobi(
        const std::vector<
            boost::function<double(double, double, double, double)> >&
            functions,
        const ublas::vector_expression<E>& vec,
        const double delta)
    {
        ublas::matrix<double> result(4, 4, 0.0);
        for (std::size_t i = 0; i < 4; ++i) {
            ublas::noalias(ublas::row(result, i))
                = derivative(functions[i], vec, delta);
        }
        return result;
    }

    template <typename E> inline
    ublas::vector<double> calculate(
        const std::vector<
            boost::function<double(double, double, double, double)> >&
            functions,
        const ublas::vector_expression<E>& vec)
    {
        ublas::vector<double> result(4, 0.0);
        for (std::size_t i = 0; i < 4; ++i) {
            result(i) = functions[i](vec()(0), vec()(1), vec()(2), vec()(3));
        }
        return result;
    }

    double targetFunction(
        const boost::function<double(double)>& function,
        const double input,
        const double target);

    boost::function<double(double)> makeTargetFunction(
        const boost::function<double(double)>& function,
        const double target);

    inline
    double newton(
        const boost::function<double(double)>& function,
        const double initial,
        const std::size_t maxIteration,
        const double tolerance)
    {
        double current(initial);
        double previous(initial);
        for (std::size_t i = 0; i < maxIteration; ++i) {
            const double jacobi = derivative(function, current, 1e-10);
            current -= function(current) / jacobi;
            if (std::abs(current - previous) < tolerance) {
                break;
            }
            previous = current;
        }
        return current;
    }

    template <typename E> inline
    ublas::vector<double> newton(
        const std::vector<
            boost::function<double(double, double, double, double)> >&
            functions,
        const ublas::vector_expression<E>& initials,
        const std::size_t maxIteration,
        const double tolerance)
    {
        ublas::vector<double> current(initials());
        ublas::vector<double> previous(initials());
        for (std::size_t i = 0; i < maxIteration; ++i) {
            const ublas::matrix<double> jacobi_matrix(
                jacobi(functions, current, 1e-10));
            current -= ublas::prod(
                numeric::invert(jacobi_matrix), calculate(functions, current));
            if (ublas::norm_2(current - previous) < tolerance) {
                break;
            }
            previous = current;
        }
        return current;
    }


}  // namespace numeric



#endif // NUMERIC_H_INCLUDED
