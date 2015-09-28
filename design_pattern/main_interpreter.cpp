#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Context.h"
#include "FactorNode.h"
#include "ExpressionNode.h"
#include "TermNode.h"
#include "Calculator.h"

int main() 
{
    const std::string expression = "( 2 + ( 2 + 3 / 2 - 1 ) )";
    design_pattern::Calculator calculator;
    const double result = calculator.calc(expression);
    std::cout << result << std::endl;
    return 0;
}