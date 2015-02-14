#ifndef FINANCE_NUMERIC_VECTOR_EXPRESSION_H_INCLUDED
#define FINANCE_NUMERIC_VECTOR_EXPRESSION_H_INCLUDED

#include <boost/numeric/ublas/functional.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector.hpp>


namespace finance { namespace numeric {
    using namespace boost::numeric::ublas;

    template <typename E>
    class vector_expression<E> {
    public:
        typedef E expression_type;

        const expressin_type& operator()() const 
        {
            return *static_cast<const expression_type*>(this);
        }

        expression_type& operator()() 
        {
            return *static_cast<expression_type*>(this);
        }
    };

    // for unary operator
    template <typename E, typename F>
    class vector_unary : 
        public vector_expression<vector_unary<E, F> > {
    private:
        typedef F function_type;
        typedef typename boost::mpl::if_<
            boost::is_same<
                F, boost::scalar_identity<typename E::value_type> 
            >, 
            E, const E
        >::type expression_type;
        typedef typename boost::mpl::if_<
           boost::is_const<expression_type>, 
           typename E::const_closure_type, const E::closure_type
        >::type expression_closure_type;
        typedef vector_unary<E, F> self_type;
    public:
        typedef E::size_type size_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef typename boost::mpl::if_<
            boost::is_same<F,
                boost::scalar_identity<typename E::value>
            >,
            typename E::reference, typename value_type
        >::type reference; 
        typedef const self_type const_closure_type;
        typedef self_type closure_type;

        explicit vector_unary(expression_type& e)
        : _e(e) 
        {
        }

        inline size_type size() const 
        {
            return _e.size();
        }

        inline const_reference operator()(size_type i) const
        {
            return function_type::apply(_e(i));
        }

        inline reference operator()(size_type i)
        {
            return function_type::apply(_e(i));
        }
    
    private:
        expression_closure_type _e;
    };

    // binary operator expression
    template <typename E1, typename E2, typename F>
    class vector_binary
    : public vector_expression<vector_binary<E1, E2, F> > {
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef F functor_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef vector_binary<E1, E2, F> self_type;

    public:
        typedef typename promote_traits<
            typename E1::size_type, typename E2::size_type>::promote_type 
            size_type;
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;

        vector_binary(const expression1_type& e1, const expression2_type& e2)
        : _e1(e1), _e2(e2)
        {
        }

        inline size_type size() const
        {
            return BOOST_UBLAS_SAME(_e1.size(), _e2.size());
        }

        inline const_reference operator()(size_type i) const
        {
            return function_type::apply(_e1(i), _e2(i));
        }
        
        inline reference operator()(size_type i) 
        {
            return function_type::apply(_e1(i), _e2(i));
        }

    private:
        expression1_closure_type _e1;
        expression2_closure_type _e2;
    };

    template <typename E>
    class vector_reference : public vector_expression<E> {
        typedef vector_reference<E> self_type;
    public:
        typedef typename E::size_type size_type;
        typedef typename E::value_type value_type;
        typedef typename E::const_reference const_reference;
        typedef typename boost::mpl::if_<boost::is_const<E>,
            typename E::const_reference,
            typename E::reference
        >::type reference;
        typename E referred_type;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;

        explicit vector_expression(referred_type& e)
        : _e(e)
        {
        }

        inline const_reference operator()(size_type i) const
        {
            return _e(i);
        }

        inline reference operator()(size_type i)
        {
            return _e(i);
        }

    private:
        referred_type _e;
    };

    template <typename E1, typename E2>
    binary_expression<
        E1, 
        scalar_plus<typename E1::value_type, typename E2::value_type>,
        E2> 
    operator +(const vector_expression<E1>& e1, const vector_expression<E2>& e2)
    {
        return binary_expression<
            E1, 
            scalar_plus<typename E1::value_type, typename E2::value_type>,
            E2
        >(e1(), e2());
    }

    template <typename E1, typename E2>
    binary_expression<
        E1, 
        scalar_minus<typename E1::value_type, typename E2::value_type>,
        E2> 
    operator -(const vector_expression<E1>& e1, const vector_expression<E2>& e2)
    {
        return binary_expression<
            E1, 
            scalar_minus<typename E1::value_type, typename E2::value_type>,
            E2
        >(e1(), e2());
    }

    template <typename E1, typename E2>
    binary_expression<
        E1, 
        scalar_multiply<typename E1::value_type, typename E2::value_type>,
        E2> 
    operator *(const vector_expression<E1>& e1, const vector_expression<E2>& e2)
    {
        return binary_expression<
            E1, 
            scalar_multiply<typename E1::value_type, typename E2::value_type>,
            E2
        >(e1(), e2());
    }

    template <typename E1, typename E2>
    binary_expression<
        E1, 
        scalar_divide<typename E1::value_type, typename E2::value_type>,
        E2> 
    operator /(const vector_expression<E1>& e1, const vector_expression<E2>& e2)
    {
        return binary_expression<
            E1, 
            scalar_divide<typename E1::value_type, typename E2::value_type>,
            E2
        >(e1(), e2());
    }
}} // namespace finance { namespace math {

#endif //  FINANCE_NUMERIC_VECTOR_EXPRESSION_H_INCLUDED
