/*
 * CommandPricer.h
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#ifndef COMMANDPRICER_H_INCLUDED
#define COMMANDPRICER_H_INCLUDED

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>
#include "YieldCurve.h"
#include "MarketDataSet.h"
#include "SabrModelParameter.h"
#include "SabrCalibrator.h"
#include "SabrPricer.h"

namespace design_pattern {
    class CommandPricerMemento {
    private:
        friend class CommandPricer;

        CommandPricerMemento(const YieldCurve& yieldCurve,
            const SabrCalibrator& calibrator,
            const SabrPricer& pricer,
            const std::vector<double>& prices)
        : _yieldCurve(yieldCurve.clone()), _calibrator(calibrator.clone()),
            _pricer(pricer.clone()), _prices(prices)
        {
        }

        void setParameters(const YieldCurve& yieldCurve,
            const SabrCalibrator& calibrator,
            const SabrPricer& pricer,
            const std::vector<double>& prices)
        {
            _yieldCurve = yieldCurve.clone();
            _calibrator = calibrator.clone();
            _pricer = pricer.clone();
            _prices = prices;
        }

        const boost::shared_ptr<YieldCurve>& yieldCurve() const
        {
            return _yieldCurve;
        }

        const boost::shared_ptr<SabrCalibrator>& calibrator() const
        {
            return _calibrator;
        }

        const boost::shared_ptr<SabrPricer>& pricer() const
        {
            return _pricer;
        }

        const std::vector<double>& prices() const
        {
            return _prices;
        }

        boost::shared_ptr<YieldCurve> _yieldCurve;
        boost::shared_ptr<SabrCalibrator> _calibrator;
        boost::shared_ptr<SabrPricer> _pricer;
        std::vector<double> _prices;
    };

    class CommandPricer {
    public:
        CommandPricer(const YieldCurve& yieldCurve,
            const SabrCalibrator& calibrator,
            const SabrPricer& pricer)
        : _yieldCurve(yieldCurve.clone()), _calibrator(calibrator.clone()),
            _pricer(pricer.clone()), _prices()
        {
        }

        void constructYieldCurve(const std::string& filePath) const
        {
            // make YieldCurve
            const YieldCurveDataSet dataset = parseYieldCurveDataSet(filePath);
            _yieldCurve->setYieldCurveDataSet(dataset);
            _yieldCurve->build();
        }

        void calibrateModelParameter(const std::string& filePath)
        {
            // calibrate ModelParameter
            const VolatilityDataSet dataset = parseVolatilityDataSet(filePath);
            _pricer = boost::make_shared<SabrPricer>(
                _calibrator->calibrate(dataset), *_yieldCurve);
        }

        void calculatePrice(const double spot, const double maturity,
            const double strike)
        {
            // pricing
            _prices.push_back(_pricer->calculatePrice(spot, maturity, strike));
        }

        const std::vector<double>& prices() const
        {
            return _prices;
        }

        boost::shared_ptr<CommandPricerMemento> createMemento() const
        {
            return boost::shared_ptr<CommandPricerMemento>(
                new CommandPricerMemento(
                    *_yieldCurve, *_calibrator, *_pricer, _prices));
        }

        void setMemento(
            const boost::shared_ptr<CommandPricerMemento>& memento)
        {
            _yieldCurve = memento->yieldCurve()->clone();
            _calibrator = memento->calibrator()->clone();
            _pricer = memento->pricer()->clone();
            _prices = memento->prices();
        }

    private:
        CommandPricer(const CommandPricer& other);
        CommandPricer& operator =(const CommandPricer& other);
        boost::shared_ptr<YieldCurve> _yieldCurve;
        boost::shared_ptr<SabrCalibrator> _calibrator;
        boost::shared_ptr<SabrPricer> _pricer;
        std::vector<double> _prices;
    };

}

#endif // COMMANDPRICER_H_INCLUDED
