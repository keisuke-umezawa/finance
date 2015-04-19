#ifndef AUTO_DIF_POLYNOMIAL_H_INCLUDED
#define AUTO_DIF_POLYNOMIAL_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <functional>

namespace finance { namespace auto_diff {
    namespace ublas = boost::numeric::ublas;

    template <typename T, std::size_t N>
    class Polynomial {
    public:
        typedef T value_type;
        typedef value_type result_type;
        typedef std::size_t size_type;
    public:
        Polynomial()
        : _coefficients()
        {
        }

        template <typename E>
        Polynomial(const ublas::vector_expression<E>& coefficients)
        : _coefficients(coefficients())
        {
        }

        inline result_type operator()(const value_type& value) const 
        {
            value_type sum(0);
            for (std::size_t i = 0; i < N; ++i) {
                sum += pow(value, i) * _coefficients(i);
            }
            return sum;
        }
        
        inline size_type degree() const
        {
            return N;
        }

        template <typename E>
        void setCoefficients(const ublas::vector_expression<E>& coefficients)
        {
            _coefficients = coefficients;
        }

    private:
        ublas::c_vector<T, N> _coefficients;
    };

    template <typename T, std::size_t N>
    class CalibratingPolynomial {
    public:
        typedef T value_type;
        typedef value_type result_type;
        typedef std::size_t size_type;
    public:
        CalibratingPolynomial(const value_type& input)
        : _polynomial(), _input(input)
        {
        }

        template <typename E>
        inline result_type operator()(
            const ublas::vector_expression<E>& coefficients) 
        {
            _polynomial.setCoefficients(coefficients);
            return _polynomial(_input);
        }
        
    private:
        Polynomial<T, N> _polynomial;
        const value_type _input;
    };

    // ------------------------------------------------------------------------
    // Dispatcher
    // ------------------------------------------------------------------------

    template<std::size_t N, typename E> inline
    Polynomial<typename E::value_type, N> 
    makePolynomial(const ublas::vector_expression<E>& e)
    {
        return Polynomial<typename E::value_type, N>(e());
    }

    template<std::size_t N, typename T> inline
    CalibratingPolynomial<T, N> 
    makeCalibratingPolynomial(const T& input)
    {
        return CalibratingPolynomial<T, N>(input);
    }

}} // namespace finance { namespace auto_diff {

#endif //  AUTO_DIF_POLYNOMIAL_H_INCLUDED
