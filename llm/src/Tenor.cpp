/*
 * Tenor.cpp
 *
 *  Created on: 2015/05/12
 *      Author: Keisuke
 */

#include "Tenor.h"

namespace lmm {

    date_t addDays(const date_t& date, const std::size_t n)
    {
        return date + boost::gregorian::date_duration(n);
    }

    date_t addMonths(const date_t& date, const std::size_t n)
    {
        return date + boost::gregorian::months(n);
    }

    date_t addYears(const date_t& date, const std::size_t n)
    {
        return date + boost::gregorian::years(n);
    }

    date_t addTenor(const date_t& date, const Tenor& tenor)
    {
        if (tenor.unit() == TenorUnit::Day) {
            return addDays(date, tenor.number());
        }
        if (tenor.unit() == TenorUnit::Week) {
            return addDays(date, 7 * tenor.number());
        }
        if (tenor.unit() == TenorUnit::Month) {
            return addMonths(date, tenor.number());
        }
        if (tenor.unit() == TenorUnit::Year) {
            return addYears(date, tenor.number());
        }
        return date;
    }

}  // namespace lmm



