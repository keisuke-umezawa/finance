#ifndef STRIPCAPLET_VOLATILTIES_H_INCLUDED
#define STRIPCAPLET_VOLATILTIES_H_INCLUDED

#include <cmath>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd.h"
#include "YieldCurve.h"

namespace lmm {

    ublas::vector<double> makeCapletVolatilities(
        const date_t& today,
        const ublas::vector<date_t>& dates,
        const IYieldCurve& yieldCurve,
        const ublas::vector<double>& capStrikes,
        const ublas::vector<double>& capVolatililies);

}  // namespace lmm



#endif // STRIPCAPLET_VOLATILTIES_H_INCLUDED
