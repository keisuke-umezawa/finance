#include "Integral.h"
#include "DayCountFraction.h"
#include "IDeterministicProcess.h"


namespace finance {
    typedef boost::gregorian::date date_type;

    double integral(const ConstantProcess& integrand,
        const date_type& t0, const date_type& t1)
    {
        return dayCountAct365(t0, t1) * integrand(t0);
    }

} // namespace finance
