#ifndef FINANCE_INTEGRAL_H_INCLUDED
#define FINANCE_INTEGRAL_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace finance {
    class ConstantProcess;
}

namespace finance {
    typedef boost::gregorian::date date_type;

    double integral(const ConstantProcess& integrand,
        const date_type& t0, const date_type& t1);

} // namespace finance

#endif // FINANCE_INTEGRAL_H_INCLUDED
