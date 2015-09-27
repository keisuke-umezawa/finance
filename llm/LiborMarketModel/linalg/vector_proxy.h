#ifndef LINALG_VECTOR_PROXY_H_INCLUDED
#define LINALG_VECTOR_PROXY_H_INCLUDED

#include <algorithm>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

namespace linalg {
    namespace ublas = boost::numeric::ublas;

    template<typename T> inline
    void push_back(ublas::vector<T>& vector, const T& value)
    {
        return;
    }
    template<typename T> inline
    void push_front(ublas::vector<T>& vector, const T& value)
    {
        vector.resize(vector.size() + 1);
        std::copy(vector.rbegin() + 1, vector.rend(), vector.rbegin());
        vector(0) = value;
    }
    template<typename T> inline
    ublas::vector<T> add_front(
        const ublas::vector<T>& vector, const T& value)
    {
        ublas::vector<T> copy(vector);
        push_front(copy, value);
        return copy;
    }
}

#endif // LINALG_VECTOR_PROXY_H_INCLUDED
