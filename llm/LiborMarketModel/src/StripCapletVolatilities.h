#ifndef STRIPCAPLET_VOLATILTIES_H_INCLUDED
#define STRIPCAPLET_VOLATILTIES_H_INCLUDED

#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "Tenor.h"
#include "YieldCurve.h"
#include "LinearInterpolant.h"

namespace lmm {

    ublas::vector<double> stripCapletVolatilities(
        const IYieldCurve& yieldCurve,
        const date_t& today,
        const Tenor& periods,
        const Tenor& termination,
        const IInterpolant& capVolatilityInterpolant);

}  // namespace lmm



#endif // STRIPCAPLET_VOLATILTIES_H_INCLUDED
