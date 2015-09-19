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

    private:
        std::size_t _number;
        TenorUnit _unit;
    };

    date_t addDays(const date_t& date, const std::size_t n);

    date_t addMonths(const date_t& date, const std::size_t n);

    date_t addYears(const date_t& date, const std::size_t n);

    date_t addTenor(const date_t& date, const Tenor& tenor);
}  // namespace lmm



#endif // TENOR_H_INCLUDED
