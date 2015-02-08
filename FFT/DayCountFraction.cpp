#include "DayCountFraction.h"

namespace finance {
    typedef boost::gregorian::date date_type;

    double dayCountAct365(const date_type& startDate,
        const date_type& endDate)
    {
        return (endDate - startDate).days() / 365.0;
    }
} // namespace finance
