#ifndef MARKETDATA_H_INCLUDED
#define MARKETDATA_H_INCLUDED

#include "fwd.h"

namespace design_pattern {

    class DepositeRateMarketData {
    public:
        void setStartDate(const date_t& data)
        {
            _startDate = data;
        }

        void setQuote(const double quote)
        {
            _quote = quote;
        }

        const date_t& startDate() const
        {
            return _startDate;
        }

        const double quote() const
        {
            return _quote;
        }

    private:
        date_t _startDate;
        double _quote;
    };

    class ForwardRateAgreementMarketData {
    public:
        void setStartDate(const date_t& data)
        {
            _startDate = data;
        }

        void setEndDate(const date_t& date)
        {
            _endDate = date;
        }

        void setQuote(const double quote)
        {
            _quote = quote;
        }

        const date_t& startDate() const
        {
            return _startDate;
        }

        const date_t& endDate() const
        {
            return _endDate;
        }

        const double quote() const
        {
            return _quote;
        }

    private:
        date_t _startDate;
        date_t _endDate;
        double _quote;
    };

    class SwapRateMarketData {
    public:
        void setStartDate(const date_t& data)
        {
            _startDate = data;
        }

        void setTenor(const tenor_t& tenor)
        {
            _tenor = tenor;
        }

        void setQuote(const double quote)
        {
            _quote = quote;
        }

        const date_t& startDate() const
        {
            return _startDate;
        }

        const tenor_t& tenor() const
        {
            return _tenor;
        }

        const double quote() const
        {
            return _quote;
        }

    private:
        date_t _startDate;
        tenor_t _tenor;
        double _quote;
    };
}

#endif // MARKETDATA_H_INCLUDED