#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Fwd.h"
#include "YieldCurveCreator.h"
#include "YieldCurve.h"
#include "CalcDiscountFactor.h"

int main()
{
    const design_pattern::date_t today = "today";

    // OisYieldCurve
    {
        const design_pattern::YieldCurveCreator& factory
            = design_pattern::OisYieldCurveCreator();
        const double df
            = design_pattern::calcDiscountFactor(today, factory);
        std::cout << df << std::endl;
    }

    // LiborYieldCurve
    {
        const design_pattern::YieldCurveCreator& factory
            = design_pattern::LiborYieldCurveCreator();
        const double df
            = design_pattern::calcDiscountFactor(today, factory);
        std::cout << df << std::endl;
    }


    return 0;
}