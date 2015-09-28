
#include "numeric/eigen.h"
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/symmetric.hpp>
#define BOOST_NUMERIC_BINDINGS_USE_CLAPACK
#include <boost/numeric/bindings/lapack/sygv.hpp>
#include <boost/numeric/bindings/traits/std_vector.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#undef BOOST_NUMERIC_BINDINGS_USE_CLAPACK


namespace numeric {
    void eigen(
        const ublas::symmetric_matrix<double>& A,
        const ublas::symmetric_matrix<double>& B,
        ublas::matrix<double>& Z, 
        ublas::vector<double>& d)
    {
        namespace lapack = boost::numeric::bindings::lapack;

        BOOST_UBLAS_CHECK(A.size1() == B.size1(), ublas::external_logic());

        ublas::vector<double> cd(A.size1());
        ublas::matrix<double, ublas::column_major> 
            CA(A.size1(), A.size2()), CB(B.size1(), B.size2());
        int info = 0;

        for (std::size_t i = 0; i < A.size1(); ++i) {
            for (std::size_t j = 0; j <= i; ++j) {
                CA(i, j) = A(i, j);
                CB(i, j) = B(i, j);
            }
        }

        info = lapack::sygv(1, 'V', 'L', CA, CB, cd, 
            lapack::optimal_workspace());
        BOOST_UBLAS_CHECK(info == 0, ublas::internal_logic());

        Z = CA;
        d.swap(cd);
    }
}  // namespace numeric


