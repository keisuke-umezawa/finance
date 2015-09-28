#include <limits>
#include <boost/shared_ptr.hpp>
#include "InterpolantMixin.h"

namespace design_pattern {

    //const double LinearInterpolant::operator()(const double x) const
    //{
    //    double previousAbscissa = _abscissas(0);
    //    double previousOrdinate = _ordinates(0);
    //    for (std::size_t i = 1; i < _abscissas.size(); ++i) {
    //        if (x < _abscissas(i)) {
    //            return previousOrdinate 
    //                + (_ordinates(i) - previousOrdinate) 
    //                * (x - previousAbscissa)
    //                / (_abscissas(i) - previousAbscissa);
    //        }
    //        previousAbscissa = _abscissas(i);
    //        previousOrdinate = _ordinates(i);
    //    }
    //    return previousOrdinate 
    //        + (_ordinates(_ordinates.size()) - previousOrdinate) 
    //        * (x - previousAbscissa)
    //        / (_abscissas(_abscissas.size()) - previousAbscissa);
    //}

    //void LinearInterpolant::init(
    //    const ublas::vector<double>& ordinates,
    //    const ublas::vector<double>& abscissas)
    //{
    //    _ordinates = ordinates;
    //    _abscissas = abscissas;
    //}

}