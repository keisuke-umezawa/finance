#ifndef INVERT_H_INCLUDED
#define INVERT_H_INCLUDED

#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace numeric {
    namespace ublas = boost::numeric::ublas;

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

    template <typename E> inline
    ublas::matrix<double> pseudo_invert(const ublas::matrix_expression<E>& input)
    {
        ublas::matrix<double> input_copy(input);
        if (input_copy.size1() > input_copy.size2()) {
            return ublas::prod(
                    invert(ublas::prod(ublas::trans(input_copy), input_copy)),
                    ublas::trans(input_copy));
        }
        return ublas::prod(ublas::trans(input_copy),
            invert(ublas::prod(input_copy, ublas::trans(input_copy))));
    }



}  // namespace numeric

#endif // INVERT_H_INCLUDED
