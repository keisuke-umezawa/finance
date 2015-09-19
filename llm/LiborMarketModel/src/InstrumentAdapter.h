/*
 * InstrumentAdapter.h
 *
 *  Created on: 2015/05/10
 *      Author: Keisuke
 */

#ifndef INSTRUMENTADAPTER_H_INCLUDED
#define INSTRUMENTADAPTER_H_INCLUDED

namespace lmm {
    class IInstrumentAdapter {
    public:
        virtual ~IInstrumentAdapter() {}

        const ublas::vector<double>& rates() const
        {
            return doRates();
        }

        const ublas::vector<date_t>& legs() const
        {
            return doLegs();
        }

        boost::shared_ptr<IInstrumentAdapter> clone() const
        {
            return boost::shared_ptr<IInstrumentAdapter>(this->doClone());
        }

    private:
        virtual const ublas::vector<double>& doRates() const = 0;

        virtual const ublas::vector<date_t>& doLegs() const = 0;

        virtual IInstrumentAdapter* doClone() const = 0;
    };

    class CapletAdapter : public IInstrumentAdapter {
    public:
        explicit CapletAdapter(const Caplet& caplet)
        : _caplet(caplet), _rates(), _legs()
        {
        }

        virtual ~CapletAdapter() {}

        virtual const ublas::vector<double>& rates() const
        {
            // TODO
            // return ublas::vector<double>(5, _caplet.rate());
            return _rates;
        }

        virtual const ublas::vector<date_t>& legs() const
        {
            // TODO
            // return ublas::vector<date_t>(5, _caplet.leg());
            return _legs;
        }

    private:
        virtual const ublas::vector<double>& doRates() const
        {
            // TODO
            // return ublas::vector<double>(5, _caplet.rate());
            return _rates;
        }

        virtual const ublas::vector<date_t>& doLegs() const
        {
            // TODO
            // return ublas::vector<date_t>(5, _caplet.leg());
            return _legs;
        }

        virtual CapletAdapter* doClone() const
        {
            return new CapletAdapter(*this);
        }

        const Caplet _caplet;
        ublas::vector<double> _rates;
        ublas::vector<date_t> _legs;
    };

    class CapAdapter : public IInstrumentAdapter {
    public:
        explicit CapAdapter(const Cap& cap)
        : _cap(cap)
        {
        }

        virtual ~CapAdapter() {}

    private:
        virtual const ublas::vector<double>& doRates() const
        {
            return _cap.rates();
        }

        virtual const ublas::vector<date_t>& doLegs() const
        {
            return _cap.legs();
        }

        virtual CapAdapter* doClone() const
        {
            return new CapAdapter(*this);
        }

        const Cap _cap;
    };

}  // namespace lmm



#endif // INSTRUMENTADAPTER_H_INCLUDED
