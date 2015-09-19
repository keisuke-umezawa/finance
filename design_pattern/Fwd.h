#ifndef FWD_H_INCLUDED
#define FWD_H_INCLUDED

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

namespace design_pattern {
    namespace ublas = boost::numeric::ublas;
    typedef std::string date_t;
    typedef std::string tenor_t;
}

#endif // FWD_H_INCLUDED