#ifndef AUTO_DIF_DUALFUNCTION_H_INCLUDED
#define AUTO_DIF_DUALFUNCTION_H_INCLUDED


#include <cmath>
#include "Dual.h"

namespace finance { namespace auto_diff {
    using std::exp;
    using std::sqrt;
    using std::abs;
    using std::pow;

    template <typename T, typename I> inline
    Dual<T, I> exp(const Dual<T, I>& dual)
    {
        return Dual<T, I>(exp(dual.real()), 
            dual.infinitesimal() * exp(dual.real()));
    }

    template <typename T, typename I> inline
    Dual<T, I> sqrt(const Dual<T, I>& dual)
    {
        return Dual<T, I>(sqrt(dual.real()), 
            dual.infinitesimal() / (T(2) * dual.real()));
    }

    template <typename T, typename I> inline
    Dual<T, I> abs(const Dual<T, I>& dual)
    {
        if (dual.real() > 0) {
            return Dual<T, I>(abs(dual.real()), 
                dual.infinitesimal());
        }
        return Dual<T, I>(abs(dual.real()), 
            -dual.infinitesimal());
    }

    template <typename T, typename I, typename P> inline
    Dual<T, I> pow(const Dual<T, I>& dual, const P& p)
    {
        return Dual<T, I>(pow(dual.real(), p), 
            dual.infinitesimal() * p * pow(dual.real(), p - P(1)));
    }
}} // namespace finance { namespace auto_diff {

#endif //  AUTO_DIF_DUALFUNCTION_H_INCLUDED
