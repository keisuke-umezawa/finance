#ifndef FINANCE_CALCCHARACTERISTICFUNCTION_H_INCLUDED
#define FINANCE_CALCCHARACTERISTICFUNCTION_H_INCLUDED

#include <complex>

namespace finance {

    std::complex<double> calcCharacteristicFunction(
            const std::complex<double>& wave, const BsModel& sde);
} // namespace finance

#endif // FINANCE_CALCCHARACTERISTICFUNCTION_H_INCLUDED
