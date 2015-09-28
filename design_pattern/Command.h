/*
 * Command.h
 *
 *  Created on: 2015/05/21
 *      Author: Keisuke
 */

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "CommandPricer.h"

namespace design_pattern {

    class Command {
    public:
        virtual ~Command() {}

        boost::shared_ptr<Command> clone() const
        {
            return boost::shared_ptr<Command>(doClone());
        }

        void execute() const
        {
            this->doExecute();
        }

        void undo() const
        {
            this->doUndo();
        }

    private:
        virtual Command* doClone() const = 0;

        virtual void doExecute() const = 0;
        virtual void doUndo() const =  0;
    };

    class ConstructYieldCurveCommand : public Command {
    public:
        ConstructYieldCurveCommand(
            const boost::shared_ptr<CommandPricer>& commandPricer,
            const std::string& filePath)
        : _commandPricer(commandPricer), _filePath(filePath), 
            _memento()
        {
        }

        virtual ~ConstructYieldCurveCommand() {}

    private:
        ConstructYieldCurveCommand(const ConstructYieldCurveCommand& other)
        : _commandPricer(other._commandPricer),
            _filePath(other._filePath), 
            _memento()
        {
        }

        ConstructYieldCurveCommand& operator =(
            const ConstructYieldCurveCommand& other);

        virtual ConstructYieldCurveCommand* doClone() const
        {
            return new ConstructYieldCurveCommand(*this);
        }

        virtual void doExecute() const
        {
            _memento = _commandPricer->createMemento();
            _commandPricer->constructYieldCurve(_filePath);
        }

        virtual void doUndo() const
        {
            _commandPricer->setMemento(_memento);
        }

        const boost::shared_ptr<CommandPricer> _commandPricer;
        const std::string _filePath;
        mutable boost::shared_ptr<CommandPricerMemento> _memento;
    };

    class CalibrateModelParameterCommand : public Command {
    public:
        CalibrateModelParameterCommand(
            const boost::shared_ptr<CommandPricer>& commandPricer,
            const std::string& filePath)
        : _commandPricer(commandPricer), _filePath(filePath), 
            _memento()
        {
        }

        virtual ~CalibrateModelParameterCommand() {}

    private:
        CalibrateModelParameterCommand(
            const CalibrateModelParameterCommand& other)
        : _commandPricer(other._commandPricer),
            _filePath(other._filePath), 
            _memento()
        {
        }

        CalibrateModelParameterCommand& operator =(
            const CalibrateModelParameterCommand& other);

        virtual CalibrateModelParameterCommand* doClone() const
        {
            return new CalibrateModelParameterCommand(*this);
        }

        virtual void doExecute() const
        {
            _memento = _commandPricer->createMemento();
            _commandPricer->calibrateModelParameter(_filePath);
        }

        virtual void doUndo() const
        {
            _commandPricer->setMemento(_memento);
        }

        const boost::shared_ptr<CommandPricer> _commandPricer;
        const std::string _filePath;
        mutable boost::shared_ptr<CommandPricerMemento> _memento;
    };

    class CalculatePriceCommand : public Command {
    public:
        CalculatePriceCommand(
            const boost::shared_ptr<CommandPricer>& commandPricer,
            const double spot, const double maturity, const double strike)
        : _commandPricer(commandPricer), _spot(spot), 
            _maturity(maturity), _strike(strike), 
            _memento()
        {
        }

        virtual ~CalculatePriceCommand() {}

    private:
        CalculatePriceCommand(const CalculatePriceCommand& other)
        : _commandPricer(other._commandPricer),
            _spot(other._spot), _maturity(other._maturity),
            _strike(other._strike), 
            _memento()
        {
        }

        CalculatePriceCommand& operator =(const CalculatePriceCommand& other);

        virtual CalculatePriceCommand* doClone() const
        {
            return new CalculatePriceCommand(*this);
        }

        virtual void doExecute() const
        {
            _memento = _commandPricer->createMemento();
            _commandPricer->calculatePrice(_spot, _maturity, _strike);
        }

        virtual void doUndo() const
        {
            _commandPricer->setMemento(_memento);
        }        

        const boost::shared_ptr<CommandPricer> _commandPricer;
        const double _spot;
        const double _maturity;
        const double _strike;
        mutable boost::shared_ptr<CommandPricerMemento> _memento;
    };

    class MacroCommand : public Command {
    public:
        MacroCommand() 
        : _commands()
        {
        }

        virtual ~MacroCommand() {}

        void add(const Command& command)
        {
            _commands.push_back(command.clone());
        }

    private:
        MacroCommand(const MacroCommand& other)
        : _commands()
        {
            for (std::size_t i = 0; i < other._commands.size(); ++i) {
                _commands.push_back(other._commands[i]->clone());
            }
        }

        MacroCommand& operator =(const MacroCommand& other);

        virtual MacroCommand* doClone() const
        {
            return new MacroCommand(*this);
        }

        virtual void doExecute() const
        {
            typedef BOOST_TYPEOF(_commands.begin()) itr;
            for (itr c = _commands.begin(); c != _commands.end(); ++c) {
                (*c)->execute();
            }
        }

        virtual void doUndo() const
        {
            typedef BOOST_TYPEOF(_commands.rbegin()) ritr;
            for (ritr c = _commands.rbegin(); c != _commands.rend(); ++c) {
                (*c)->undo();
            }
        }

        std::vector<boost::shared_ptr<const Command> > _commands;
    };

    class CommandInvoker {
    public:
        CommandInvoker() : _commands() {}

        void add(const Command& command)
        {
            _commands.push_back(command.clone());
        }

        void execute() const
        {
            typedef BOOST_TYPEOF(_commands.begin()) itr;
            for (itr c = _commands.begin(); c != _commands.end(); ++c) {
                (*c)->execute();
            }
        }

        void undo()
        {
            _commands.back()->undo();
            _commands.pop_back();
        }

    private:
        CommandInvoker(const CommandInvoker& other);
        CommandInvoker& operator =(const CommandInvoker& other);
        std::list<const boost::shared_ptr<const Command> > _commands;
    };


}  // namespace design_pattern

#endif // COMMAND_H_INCLUDED
