#ifndef AUTO_DIF_DUAL_H_INCLUDED
#define AUTO_DIF_DUAL_H_INCLUDED

#include <boost/operators.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace finance { namespace auto_diff {
    namespace ublas = boost::numeric::ublas;

    // ------------------------------------------------------------------------
    // make_infinitesimal_traits
    // ------------------------------------------------------------------------
    template <typename T, typename I>
    struct make_infinitesimal_traits;

    template <typename T, std::size_t N>
    struct make_infinitesimal_traits<T, ublas::c_vector<T, N> > {
        static ublas::c_vector<T, N> apply()
        {
            return ublas::zero_vector<T>(N);
        }

        static ublas::c_vector<T, N> apply(const std::size_t index)
        {
            return ublas::unit_vector<T>(N, index);
        }
    };

    // ------------------------------------------------------------------------
    // infinitesimal_traits
    // ------------------------------------------------------------------------
    template <typename I>
    struct infinitesimal_traits;

    template <typename T>
    struct infinitesimal_traits<ublas::c_vector<T, 1> > {
        typedef T infinitesimal_type;

        static const infinitesimal_type& apply(
            const ublas::c_vector<T, 1>& infinitesimal)
        {
            return infinitesimal(0);
        }
    };

    template <typename T, std::size_t N>
    struct infinitesimal_traits<ublas::c_vector<T, N> > {
        typedef ublas::c_vector<T, N> infinitesimal_type;

        static const infinitesimal_type& apply(
            const ublas::c_vector<T, N>& infinitesimal)
        {
            return infinitesimal;
        }
    };

    template <typename T, typename I>
    class Dual : 
        private boost::less_than_comparable<Dual<T, I>,
        boost::equality_comparable<Dual<T, I>,
        boost::addable<Dual<T, I>,
        boost::subtractable<Dual<T, I>,
        boost::multipliable<Dual<T, I>,
        boost::dividable<Dual<T, I>,
        boost::addable<Dual<T, I>, T,
        boost::subtractable<Dual<T, I>, T,
        boost::subtractable2_left<Dual<T, I>, T,
        boost::multipliable<Dual<T, I>, T,
        boost::dividable<Dual<T, I>, T,
        boost::dividable2_left<Dual<T, I>, T
        > > > > > > > > > > > > {
    private:
    public:
        Dual() 
        : _real(T(0)), _infinitesimal(make_infinitesimal_traits<T, I>::apply())
        {
        }

        Dual(const T& real) 
        : _real(real), _infinitesimal(make_infinitesimal_traits<T, I>::apply())
        {
        }

        Dual(const T& real, const std::size_t index) 
        : _real(real), 
            _infinitesimal(make_infinitesimal_traits<T, I>::apply(index))
        {
        }

        template <typename E>
        Dual(const T& real, const ublas::vector_expression<E>& infinitesimal) 
        : _real(real), _infinitesimal(infinitesimal())
        {
        }

        Dual(const Dual<T, I>& dual)
        : _real(dual._real), _infinitesimal(dual._infinitesimal)
        {
        }

        const T& real() const
        {
            return _real;
        }

        const typename infinitesimal_traits<I>::infinitesimal_type& 
        infinitesimal() const
        {
            return infinitesimal_traits<I>::apply(_infinitesimal);
        }

        bool operator <(const Dual& rhs) const
        {
            return this->real() < rhs.real();
        }

        bool operator==(const Dual& rhs) const
        {
            return this->real() == rhs.real();
        }

        Dual& operator+=(const Dual& rhs)
        {
            _real += rhs._real;
            _infinitesimal += rhs._infinitesimal;
            return *this;
        }

        Dual& operator*=(const Dual& rhs)
        {
            _infinitesimal = _real * rhs._infinitesimal
                + _infinitesimal * rhs._real;
            _real *= rhs._real;
            return *this;
        }
        
        Dual& operator-=(const Dual& rhs)
        {
            _real -= rhs._real;
            _infinitesimal -= rhs._infinitesimal;
            return *this;
        }
        
        Dual& operator/=(const Dual& rhs)
        {
            _infinitesimal = (_infinitesimal 
                    - _real * rhs._infinitesimal / rhs._real)
                / rhs._real;
            _real /= rhs._real;
            return *this;
        }

        Dual& operator+=(const T& rhs)
        {
            _real += rhs;
            return *this;
        }
        Dual& operator*=(const T& rhs)
        {
            _infinitesimal *= rhs;
            _real *= rhs;
            return *this;
        }

        Dual& operator-=(const T& rhs)
        {
            _real -= rhs;
            return *this;
        }

        Dual& operator/=(const T& rhs)
        {
            _infinitesimal /= rhs;
            _real /= rhs;
            return *this;
        }

        Dual operator -() const
        {
            return Dual(-_real, -_infinitesimal);
        }
    private:
        T _real;
        I _infinitesimal;
    };

    // ------------------------------------------------------------------------
    // Dispatcher   
    // ------------------------------------------------------------------------

    template <std::size_t N, typename T> inline
    Dual<T, ublas::c_vector<T, N> > makeDual(
        const T& real, const std::size_t index)
    {
        return Dual<T, ublas::c_vector<T, N> >(real, index);
    }

    template <std::size_t N, typename T> inline
    Dual<T, ublas::c_vector<T, N> > makeDual(const T& real)
    {
        return Dual<T, ublas::c_vector<T, N> >(real);
    }

    template <std::size_t N, typename T> inline
    Dual<T, ublas::c_vector<T, N> > makeDual(
        const T& real, const T& infinitesimal)
    {
        return Dual<T, ublas::c_vector<T, N> >(real,
            ublas::vector<T>(N, infinitesimal));
    }
}} // namespace finance { namespace auto_diff {

#endif //  AUTO_DIF_DUAL_H_INCLUDED
