/*
 * Instrument.cpp
 *
 *  Created on: 2015/05/23
 *      Author: Keisuke
 */

#include "fwd.h"
#include "Instrument.h"

namespace lmm {

    ublas::vector<date_t> makeLegs(
        const date_t& today, const date_t& maturity, const Tenor& tenor)
    {
        // TODO
        std::vector<date_t> legBuffer;
        for (date_t t = today; t < maturity; t = addTenor(t, tenor)) {
            legBuffer.push_back(t);
        }
        legBuffer.push_back(maturity);
        ublas::vector<date_t> legs(legBuffer.size());
        for (std::size_t i = 0; i < legBuffer.size(); ++i) {
            legs[i] = legBuffer[i];
        }
        return legs;
    }

    Cap makeCap(const double strike,
        const date_t& today, const date_t& maturity, const Tenor& tenor)
    {
        const ublas::vector<date_t> legs
            = makeLegs(today, maturity, tenor);
        const ublas::vector<double> rates(legs.size(), strike);
        return Cap(rates, legs);
    }

    Swap makeSwap(const double strike,
        const date_t& today, const date_t& maturity, const Tenor& tenor)
    {
        const ublas::vector<date_t> legs
            = makeLegs(today, maturity, tenor);
        const ublas::vector<double> rates(legs.size(), strike);
        return Swap(rates, legs);
    }

    Swaption makeSwaption(const double fixRate,
        const date_t& today, const date_t& maturity, const Tenor& tenor,
        const double strike, const bool isCall)
    {
        return Swaption(makeSwap(fixRate, today, maturity, tenor), strike, isCall);
    }


}  // namespace lmm



