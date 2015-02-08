#ifndef FINANCE_DAYCOUNTFRACTION_H_INCLUDED
#define FINANCE_DAYCOUNTFRACTION_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace finance {
    typedef boost::gregorian::date date_type;

    double dayCountAct365(const date_type& startDate,
            const date_type& endDate);
} // namespace finance

#endif // FINANCE_DAYCOUNTFRACTION_H_INCLUDED
