/*
 * Tenor.h
 *
 *  Created on: 2015/05/10
 *      Author: Keisuke
 */

#ifndef TENOR_H_INCLUDED
#define TENOR_H_INCLUDED

#include "fwd.h"

namespace lmm {
    enum class TenorUnit {
        Day = 0,
        Week,
        Month,
        Year,
        TenorUnitSize
    };

    class Tenor {
    public:
        Tenor()
        : _number(0), _unit(TenorUnit::Day)
        {
        }
        Tenor(const std::size_t number, const TenorUnit unit)
        : _number(number), _unit(unit)
        {
        }
        const std::size_t number() const
        {
            return _number;
        }

        const TenorUnit unit() const
        {
            return _unit;
        }
        friend bool operator==(const Tenor& lhs, const Tenor& rhs)
        {
            return lhs._number == rhs._number
                && lhs._unit == rhs._unit;
        }

    private:
        std::size_t _number;
        TenorUnit _unit;
    };

    date_t addDays(const date_t& date, const int n);

    date_t addMonths(const date_t& date, const int n);

    date_t addYears(const date_t& date, const int n);

    date_t addTenor(const date_t& date, const Tenor& tenor);
    
    ublas::vector<date_t> makeTenorDates(const date_t& start,
        const Tenor& periods, const Tenor& termination);

    const std::size_t toIndex(
        const Tenor& tenor, const ublas::vector<Tenor>& tenors);
}  // namespace lmm



#endif // TENOR_H_INCLUDED
