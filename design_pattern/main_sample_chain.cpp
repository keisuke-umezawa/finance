#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Instrument.h"
#include "InstrumentVisitor.h"

class ChainOfResponsibility {
public:
    ChainOfResponsibility(
        const boost::shared_ptr<const ChainOfResponsibility>& successor)
    : _successor(successor)
    {
    }
    virtual ~ChainOfResponsibility() {}
    virtual void handle(const std::size_t id) const = 0;
protected:
    virtual void next(const std::size_t id) const
    {
        if (_successor) {
            _successor->handle(id);
        }
    }
private:
    const boost::shared_ptr<const ChainOfResponsibility> _successor;
};

class ExtendChain1 : public ChainOfResponsibility {
public:
    ExtendChain1(const boost::shared_ptr<const ChainOfResponsibility>& successor)
    : ChainOfResponsibility(successor)
    {
    }
    virtual void handle(const std::size_t id) const
    {
        if (1 == id) {
            std::cout << " 1 " << std::endl;
        }
        else {
            ChainOfResponsibility::next(id);
        }
    }
};

class ExtendChain2 : public ChainOfResponsibility {
public:
    ExtendChain2(const boost::shared_ptr<const ChainOfResponsibility>& successor)
    : ChainOfResponsibility(successor)
    {
    }
    virtual void handle(const std::size_t id) const
    {
        if (2 == id) {
            std::cout << " 2 " << std::endl;
        }
        else {
            ChainOfResponsibility::next(id);
        }
    }
};

boost::shared_ptr<ChainOfResponsibility> makeChain() 
{
    return boost::make_shared<ExtendChain1>(
        boost::make_shared<ExtendChain2>(
            boost::shared_ptr<ChainOfResponsibility>()));
}

int main() 
{
    design_pattern::Cap cap;
    design_pattern::ContractDispatcher dispatcher;
    cap.accept(dispatcher);

    std::cout << dispatcher.contractType() << std::endl;

    //const boost::shared_ptr<const ChainOfResponsibility> chain
    //    = makeChain();

    //chain->handle(1);
    //chain->handle(2);

    return 0;
}