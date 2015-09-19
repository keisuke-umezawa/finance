/*
 * Instrument.h
 *
 *  Created on: 2015/04/30
 *      Author: Keisuke
 */


#ifndef INSTRUMENT_H_INCLUDED
#define INSTRUMENT_H_INCLUDED

#include <vector>
#include <boost/numeric/ublas/vector.hpp>
#include "fwd.h"
#include "Tenor.h"

namespace lmm {
    class Caplet {
    public:
        Caplet(const double strike, const date_t& today,
            const date_t& start, const date_t& end)
        : _strike(strike), _today(today), _start(start), _end(end)
        {
        }

        const double strike() const
        {
            return _strike;
        }

        const date_t& start() const
        {
            return _start;
        }

        const date_t& end() const
        {
            return _end;
        }

    private:
        const double _strike;
        const date_t _today;
        const date_t _start;
        const date_t _end;
    };

    class Cap {
    public:
        Cap(const ublas::vector<double>& rates,
            const ublas::vector<date_t>& legs)
        : _rates(rates), _legs(legs)
        {
        }

        const ublas::vector<double>& rates() const
        {
            return _rates;
        }

        const ublas::vector<date_t>& legs() const
        {
            return _legs;
        }
    private:
        ublas::vector<double> _rates;
        ublas::vector<date_t> _legs;
    };

    class Swap {
    public:
        Swap(const ublas::vector<double>& rates,
            const ublas::vector<date_t>& legs)
        : _rates(rates), _legs(legs)
        {
        }

        const ublas::vector<double>& rates() const
        {
            return _rates;
        }

        const ublas::vector<date_t>& legs() const
        {
            return _legs;
        }

    private:
        ublas::vector<double> _rates;
        ublas::vector<date_t> _legs;
    };

    class Swaption {
    public:
        Swaption(const Swap& swap, const double strike,
            const bool isCall)
        : _swap(swap), _strike(strike), _isCall(isCall)
        {
        }

        const ublas::vector<double>& rates() const
        {
            return _swap.rates();
        }

        const ublas::vector<date_t>& legs() const
        {
            return _swap.legs();
        }
    private:
        const Swap _swap;
        const double _strike;
        const bool _isCall;
    };

    ublas::vector<date_t> makeLegs(
        const date_t& today, const date_t& maturity, const Tenor& tenor);

    Cap makeCap(const double strike,
        const date_t& today, const date_t& maturity, const Tenor& tenor);

    Swap makeSwap(const double strike,
        const date_t& today, const date_t& maturity, const Tenor& tenor);

    Swaption makeSwaption(const double fixRate,
        const date_t& today, const date_t& maturity, const Tenor& tenor,
        const double strike, const bool isCall);

}

#endif // INSTRUMENT_H_INCLUDED
