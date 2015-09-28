#ifndef NUMERIC_EIGEN_H_INCLUDED
#define NUMERIC_EIGEN_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "fwd.h"
#include <boost/numeric/ublas/fwd.hpp>

namespace numeric {
    void eigen(
        const ublas::symmetric_matrix<double>& A,
        const ublas::symmetric_matrix<double>& B,
        ublas::matrix<double>& Z,
        ublas::vector<double>& d);
}  // namespace numeric
#endif // NUMERIC_EIGEN_H_INCLUDED
