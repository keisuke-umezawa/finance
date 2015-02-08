#ifndef IPAYOFF_H_INCLUDED
#define IPAYOFF_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/shared_ptr.hpp>

namespace finance {
    typedef boost::gregorian::date date_type;

    class IPayoff {
    public:
        virtual ~IPayoff() {} 

        double operator()(const double underlying) const
        {
            return doOperator(underlying);
        }

        boost::shared_ptr<IPayoff> clone() const
        {
            return boost::shared_ptr<IPayoff>(doClone());
        }

    private:
        virtual double doOperator(const double underlying) const = 0;

        virtual IPayoff* doClone() const = 0;
    };

    class CallPayoff : public IPayoff {
    public:
        CallPayoff(const double strike) : _strike(strike)
        {
        }

        virtual ~CallPayoff() {} 

        boost::shared_ptr<CallPayoff> clone() const
        {
            return boost::shared_ptr<CallPayoff>(doClone());
        }

    private:
        virtual double doOperator(const double underlying) const
        {
            return std::max(underlying - _strike, 0.0);
        }

        virtual CallPayoff* doClone() const 
        {
            return new CallPayoff(*this);
        }

        const double _strike;
    };

} // namespace finance

#endif // IPAYOFF_H_INCLUDED
