#ifndef AUTO_DIF_DUAL_H_INCLUDED
#define AUTO_DIF_DUAL_H_INCLUDED

#include <boost/operators.hpp>
#include <boost/numeric/ublas/vector.hpp>


namespace auto_diff {
    namespace ublas = boost::numeric::ublas;

    template <typename T, typename I>
    class Dual : private boost::addable<Dual<T, I>,
        boost::subtractable<Dual<T, I>,
        boost::multipliable<Dual<T, I>,
        boost::dividable<Dual<T, I>,
        boost::addable<Dual<T, I>, T,
        boost::subtractable<Dual<T, I>, T,
        boost::subtractable2_left<Dual<T, I>, T,
        boost::multipliable<Dual<T, I>, T,
        boost::dividable<Dual<T, I>, T,
        boost::dividable2_left<Dual<T, I>, T
        > > > > > > > > > > {
    private:
    public:
        Dual() : _real(T(0), _infinitesimal(make_infinitesimal_traits::apply())
        {
        }

        Dual(const T& real) : _real(real), _infinitesimal(make_infinitesimal_traits::apply())
        {
        }

        Dual(const T& real, const I& infinitesimal) 
        : _real(real), _infinitesimal(infinitesimal)
        {
        }

    private:
        T _real;
        I _infinitesimal;
    };
        
    template <typename E>
    class Infinitesimal : public ublas::vector_expression<Infinitesimal<E> > {
    private:
    public:
        Dual() : _real(T(0), _infinitesimal(make_infinitesimal_traits::apply())
        {
        }

        Dual(const T& real) : _real(real), _infinitesimal(make_infinitesimal_traits::apply())
        {
        }

        Dual(const T& real, const I& infinitesimal) 
        : _real(real), _infinitesimal(infinitesimal)
        {
        }

    private:
        T _real;
        I _infinitesimal;
    };


#endif //  AUTO_DIF_DUAL_H_INCLUDED
