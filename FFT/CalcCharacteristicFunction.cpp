#include "CalcCharacteristicFunction.h"

namespace finance {

    std::complex<double> calcCharacteristicFunction(
            const std::complex<double>& wave, const BsModel& sde)
    {
        return std::exp(1.0i * wave * finance::integral(sde.drift(), t1, t2)
                - 0.5 * finance::integral(sde.sigma() * sde.sigma(), t1, t2) 
                    * wave * wave);
    }
} // namespace finance
