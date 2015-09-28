#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <list>
#include <boost/typeof/typeof.hpp>
#include "YieldCurve.h"
#include "MarketDataSet.h"
#include "SabrModelParameter.h"
#include "SabrCalibrator.h"
#include "SabrPricer.h"
#include "CommandPricer.h"
#include "Command.h"

int main()
{
    using namespace design_pattern;
    const double beta = 1.0;
    const double tolerance = 1e-10;
    const std::size_t maxIteration = 10000;

    const boost::shared_ptr<YieldCurve> yieldCurve
        = boost::make_shared<LiborYieldCurve>();

    const SabrCalibrator calibrator(
            SabrModelParameter(), beta, tolerance, maxIteration);

    const SabrPricer pricer(SabrModelParameter(), *yieldCurve);

    const boost::shared_ptr<CommandPricer> commandPricer
        = boost::make_shared<design_pattern::CommandPricer>(
            *yieldCurve, calibrator, pricer);

    const boost::shared_ptr<Command> y1
        = boost::make_shared<ConstructYieldCurveCommand>(
            commandPricer, ".data/yield20150510.xml");
    const boost::shared_ptr<Command> y2
        = boost::make_shared<ConstructYieldCurveCommand>(
            commandPricer, ".data/yield20150511.xml");

    const boost::shared_ptr<Command> c1
        = boost::make_shared<CalibrateModelParameterCommand>(
            commandPricer, ".data/vol20150510.xml");
    const boost::shared_ptr<Command> c2
        = boost::make_shared<CalibrateModelParameterCommand>(
            commandPricer, ".data/vol20150511.xml");

    const boost::shared_ptr<Command> d1
        = boost::make_shared<CalculatePriceCommand>(
            commandPricer, 100.0, 1.0, 90.0);
    const boost::shared_ptr<Command> d2
        = boost::make_shared<CalculatePriceCommand>(
            commandPricer, 100.0, 1.0, 95.0);
    const boost::shared_ptr<Command> d3
        = boost::make_shared<CalculatePriceCommand>(
            commandPricer, 100.0, 1.0, 100.0);
    const boost::shared_ptr<Command> d4
        = boost::make_shared<CalculatePriceCommand>(
            commandPricer, 100.0, 1.0, 105.0);

    const boost::shared_ptr<MacroCommand> m1
        = boost::make_shared<MacroCommand>();
    m1->add(*d1);
    m1->add(*d2);
    m1->add(*d3);
    m1->add(*d4);

    const boost::shared_ptr<Command> m2 = m1->clone();

    CommandInvoker invoker;
    invoker.add(*y1);
    invoker.add(*c1);
    invoker.add(*m1);
    invoker.add(*y2);
    invoker.add(*c2);
    invoker.add(*m2);


    invoker.execute();
    std::vector<double> prices = commandPricer->prices();
    for (std::size_t i = 0; i < prices.size(); ++i) {
        std::cout << prices[i] << std::endl;
    }
    std::cout << std::endl;

    invoker.undo();
    prices = commandPricer->prices();
    for (std::size_t i = 0; i < prices.size(); ++i) {
        std::cout << prices[i] << std::endl;
    }

    return 0;
}
