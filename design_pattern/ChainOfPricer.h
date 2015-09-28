#ifndef CHAINOFPRICER_H_INCLUDED
#define CHAINOFPRICER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Contract.h"

namespace design_pattern {

    class ChainOfPricer {
    public:
        virtual ~ChainOfPricer() {}
        virtual double evaluate(const IContract& contract) const = 0;
    };
} // namespace design_pattern {

#endif // CHAINOFPRICER_H_INCLUDED