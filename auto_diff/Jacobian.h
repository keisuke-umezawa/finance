#ifndef AUTO_DIF_JACOBIAN_H_INCLUDED
#define AUTO_DIF_JACOBIAN_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <functional>

namespace finance { namespace auto_diff {
    namespace ublas = boost::numeric::ublas;

    // ------------------------------------------------------------------------
    // jacobian_result_traits
    // ------------------------------------------------------------------------
    
    template <typename T, typename F> 
    struct jacobian_result_traits;

    template <typename E, typename F> 
    struct jacobian_result_traits<ublas::vector_expression<E>, F> {
        typedef typename E::value_type value_type;
        typedef ublas::vector<value_type> result_type;
        static result_type apply(
            const F& f, const ublas::vector_expression<E>& input)
        {
            return result_type(input());
        }
    };

    // ------------------------------------------------------------------------
    // Dispatcher
    // ------------------------------------------------------------------------

    template <typename T, typename F>
    typename jacobian_result_traits<T, F>::result_type inline
    jacobian(const F& f, const T& input)
    {
        return jacobian_result_traits<T, F>::apply(f, input);
    }

}} // namespace finance { namespace auto_diff {

#endif //  AUTO_DIF_JACOBIAN_H_INCLUDED
