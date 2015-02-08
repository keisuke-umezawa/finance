#ifndef FINANCE_IOPTION_H_INCLUDED
#define FINANCE_IOPTION_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/shared_ptr.hpp>
#include "IPayoff.h"

namespace finance {
    typedef boost::gregorian::date date_type;

    class IOption {
    public:
        virtual ~IOption() {}

        double payoff(const double underlying) const
        {
            return doPayoff(underlying);
        }

        date_type expiryDate() const
        {
            return doExpiryDate();
        }

        boost::shared_ptr<IOption> clone() const
        {
            return boost::shared_ptr<IOption>(doClone());
        }

    private:
        virtual double doPayoff(const double underlying) const = 0;

        virtual date_type doExpiryDate() const = 0;

        virtual IOption* doClone() const = 0;
    };

    class EuropeanOption : public IOption {
    public:
        EuropeanOption(const IPayoff& payoff, const date_type expiryDate) 
        : _ptrPayoff(payoff.clone()), _expiryDate(expiryDate)
        {
        }

        virtual ~EuropeanOption() {}

        boost::shared_ptr<EuropeanOption> clone() const
        {
            return boost::shared_ptr<EuropeanOption>(doClone());
        }

    private:
        virtual double doPayoff(const double underlying) const
        {
            return (*_ptrPayoff)(underlying);
        }

        virtual date_type doExpiryDate() const 
        {
            return _expiryDate;
        }

        virtual EuropeanOption* doClone() const
        {
            return new EuropeanOption(*this);
        }

        const boost::shared_ptr<IPayoff> _ptrPayoff;
        const date_type _expiryDate;
    };

} // namespace finance

#endif // FINANCE_IOPTION_H_INCLUDED
