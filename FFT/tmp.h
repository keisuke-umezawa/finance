#ifndef FINANCE_TMP_H_INCLUDED
#define FINANCE_TMP_H_INCLUDED

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace finance {
    typedef boost::gregorian::date date_type;

    template <typename T, typename F, typename Enable = void>
    struct tmp_traits;

    template <typename T, typename Func> 
    struct tmp_traits<T, double Func(double),
            typename boost::enable_if<boost::is_float<T> >::type> {
        static T double apply(const F<T>&f, const T& x)
        {
            return f(x);
        }
    };
    
    template <typename T, typename F> inline
    T get(const F& functor, const T& x0)
    {
        return tmp_traits<T, F>().apply(functor, x0);
    }

} // namespace finance

#endif // FINANCE_TMP_H_INCLUDED_H_INCLUDED
