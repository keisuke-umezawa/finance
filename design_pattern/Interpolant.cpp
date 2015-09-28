#include <limits>
#include <boost/shared_ptr.hpp>
#include "Interpolant.h"

namespace design_pattern {

    const double LinearInterpolant::operator()(const double x) const
    {
        double previousAbscissa = 0.0;
        double previousOrdinate = 0.0;
        for (std::size_t i = 1; i < _abscissas.size(); ++i) {
            previousAbscissa = _abscissas(i - 1);
            previousOrdinate = _ordinates(i - 1);
            if (x < _abscissas(i)) {
                return previousOrdinate 
                    + (_ordinates(i) - previousOrdinate) 
                    * (x - previousAbscissa)
                    / (_abscissas(i) - previousAbscissa);
            }
            
        }
        return previousOrdinate 
            + (_ordinates(_ordinates.size() - 1) - previousOrdinate) 
            * (x - previousAbscissa)
            / (_abscissas(_abscissas.size() - 1) - previousAbscissa);
    }

    void LinearInterpolant::init(
        const ublas::vector<double>& ordinates,
        const ublas::vector<double>& abscissas)
    {
        _ordinates = ordinates;
        _abscissas = abscissas;
    }

    LinearInterpolant* LinearInterpolant::doClone() const
    {
        return new LinearInterpolant(*this);
    }

}