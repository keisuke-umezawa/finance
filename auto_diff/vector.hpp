#ifndef FINANCE_NUMERIC_VECTOR_H_INCLUDED
#define FINANCE_NUMERIC_VECTOR_H_INCLUDED

#include "vector_expression.hpp"

namespace finance { namespace numeric {

    template <typename T, std::size_t N>
    class c_vector : public vector_expression<c_vector<T, N> > {
        typedef c_vector<T, N> self_type;
    public:
        typedef const vector_reference<self_type> const_closure_type;
        typedef vector_reference<self_type> closure_type;
        typedef std::array<T, N> array_type;
        typedef typename array_type::value_type value_type;
        typedef typename array_type::size_type size_type;
        typedef typename array_type::difference_type difference_type;
        typedef T value_type;
        typedef const T& const_reference;
        typedef T& reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef self_type vector_temporary_type;

    };

}} // namespace finance { namespace math {

#endif //  FINANCE_NUMERIC_VECTOR_H_INCLUDED
