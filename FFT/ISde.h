#ifndef FINANCE_ISDE_H_INCLUDED
#define FINANCE_ISDE_H_INCLUDED

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "IDeterministicProcess.h"

namespace finance {
    typedef boost::gregorian::date date_t;

    class ISde {
    public:
        virtual ~ISde() {}

        double drift(const date_t& time, const double state) const
        {
            return doDrift(time, state);
        }

        double diffusion(const date_t& time, const double state) const
        {
            return doDiffusion(time, state);
        }

        boost::shared_ptr<ISde> clone() const
        {
            return boost::shared_ptr<ISde>(this->doClone());
        }

    private:
        virtual double doDrift(
            const date_t& time, const double state) const = 0;

        virtual double doDiffusion(
            const date_t& time, const double state) const = 0;

        virtual ISde* doClone() const = 0;

    };

    class LogNormalSde : public ISde {
    public:
        LogNormalSde(const double mu, const double sigma)
        : _mu(mu), _sigma(sigma)
        {
        }

        virtual ~LogNormalSde() {}

        boost::shared_ptr<LogNormalSde> clone() const
        {
            return boost::shared_ptr<LogNormalSde>(this->doClone());
        }

    private:
        virtual double doDrift(const date_t& time, const double state) const
        {
            return _mu(time) * state;
        }

        virtual double doDiffusion(const date_t& time, const double state) 
            const
        {
            return _sigma(time) * state;
        }

        virtual LogNormalSde* doClone() const { 
            return new LogNormalSde(*this);
        }

        const ConstantProcess _mu;
        const ConstantProcess _sigma;
    };

    class NormalSde : public ISde {
    public:
        NormalSde(const double mu, const double sigma)
        : _mu(mu), _sigma(sigma)
        {
        }

        virtual ~NormalSde() {}

        boost::shared_ptr<NormalSde> clone() const
        {
            return boost::shared_ptr<NormalSde>(this->doClone());
        }

    private:
        virtual double doDrift(const date_t& time, const double state) const
        {
            return _mu(time);
        }

        virtual double doDiffusion(const date_t& time, const double state) 
            const
        {
            return _sigma(time);
        }

        virtual NormalSde* doClone() const { 
            return new NormalSde(*this);
        }

        const ConstantProcess _mu;
        const ConstantProcess _sigma;
    };
} // namespace finance

#endif // FINANCE_ISDE_H_INCLUDED
