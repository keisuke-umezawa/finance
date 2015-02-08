#ifndef FINANCE_IDETERMINISTICPROCESS_H_INCLUDED
#define FINANCE_IDETERMINISTICPROCESS_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace finance {
    typedef boost::gregorian::date date_type;

    class IDeterministicProcess {
    public:
        virtual ~IDeterministicProcess() {}

        double operator()(const date_type& time) const
        {
            return doOperator(time);
        }

        boost::shared_ptr<IDeterministicProcess> clone() const
        {
            return boost::shared_ptr<IDeterministicProcess>(doClone());
        }

    private:
        virtual double doOperator(const date_type& time) const = 0;

        virtual IDeterministicProcess* doClone() const = 0;

    };

    class ConstantProcess : public IDeterministicProcess {
    public:
        explicit ConstantProcess(const double constant)
        : _constant(constant)
        {
        }

        virtual ~ConstantProcess() {}

        boost::shared_ptr<ConstantProcess> clone() const
        {
            return boost::shared_ptr<ConstantProcess>(doClone());
        }

    private:
        virtual double doOperator(const date_type& time) const
        {
            return _constant;
        }

        virtual ConstantProcess* doClone() const
        {
            return new ConstantProcess(*this);
        }

        const double _constant;
    };

} // namespace finance

#endif // FINANCE_IDETERMINISTICPROCESS_H_INCLUDED
