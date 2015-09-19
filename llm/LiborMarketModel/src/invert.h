/*
 * numeric.h
 *
 *  Created on: 2015/05/27
 *      Author: Keisuke
 */

#ifndef INVERT_H_INCLUDED
#define INVERT_H_INCLUDED

#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"

namespace numeric {

    template <typename E> inline
    void invert_inplace(ublas::matrix_expression<E>& matrix)
    {
        ublas::matrix<double> input_copy(matrix);
        ublas::matrix<double> rhs(
            ublas::identity_matrix<double>(matrix().size1()));
        ublas::permutation_matrix<> pm(matrix().size1());

        ublas::lu_factorize(input_copy, pm);
        ublas::lu_substitute(input_copy, pm, rhs);

        ublas::noalias(matrix()) = rhs;
    }

    template <typename E1, typename E2> inline
    void invert(const ublas::matrix_expression<E1>& input,
        ublas::matrix_expression<E2>& result)
    {
        ublas::matrix<double> input_copy(input);
        invert_inplace(input_copy);
        ublas::noalias(result()) = input_copy;
    }

    template <typename E> inline
    ublas::matrix<double> invert(const ublas::matrix_expression<E>& input)
    {
        ublas::matrix<double> input_copy(input);
        invert_inplace(input_copy);
        return input_copy;
    }

}  // namespace numeric

#endif // INVERT_H_INCLUDED
