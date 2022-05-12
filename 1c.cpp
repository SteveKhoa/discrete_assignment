#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>

using namespace std;

double sum(double a, double b)
{
    return a + b;
}
double difference(double a, double b)
{
    return a - b;
}
double product(double a, double b)
{
    return a * b;
}
double quotient(double a, double b)
{
    return a / b;
}
double power(double a, double b)
{
    return pow(a, b);
}
/**
 *  Convention:
 *      _mode
 *          = 0 : evaluate prefix string
 *          = 1 : evaluate postfix string
*/
double arithmetic_value(const string & expression, unsigned int _mode)
{
    double res = 0;
    string temp_operand = "";
    stack<string> _stack;

    // prefix evaluation
    if (_mode == 0)
    {
        for (int i = expression.size() - 1 ; i >= 0 ; --i)
        {
            if ( _stack.size() >= 2 && isOperator(expression.at(i)) )
            {
                // Getting two top operands
                double a = stod(_stack.top());
                _stack.pop();
                double b = stod(_stack.top());
                _stack.pop();

                // Evaluate & push it back to _stack
                if (expression.at(i) == '+')
                {
                    _stack.push(to_string(sum(a, b)));
                } else 
                if (expression.at(i) == '-')
                {
                    _stack.push(to_string(difference(a, b)));
                } else
                if (expression.at(i) == '*')
                {
                    _stack.push(to_string(product(a, b)));
                } else
                if (expression.at(i) == '/')
                {
                    _stack.push(to_string(quotient(a, b)));
                } else
                if (expression.at(i) == '^')
                {
                    _stack.push(to_string(power(a, b)));
                }

            } else

            if (expression.at(i) == ';')
            {
                if (temp_operand.size() > 0)
                    _stack.push(temp_operand);
                temp_operand = ""; // Clear temp_operand string, reset it to "".
            } else 

            {
                temp_operand.insert(0, 1, expression.at(i));
            }
        }

        res = stod(_stack.top());
    } else

    // postfix evaluation
    if (_mode == 1)
    {
        for (unsigned int i = 0 ; i < expression.size() ; ++i)
        {
            if ( _stack.size() >= 2 && isOperator(expression.at(i)) )
            {
                // Getting two top operands
                double b = stod(_stack.top());
                _stack.pop();
                double a = stod(_stack.top());
                _stack.pop();

                // Evaluate & push it back to _stack
                if (expression.at(i) == '+')
                {
                    _stack.push(to_string(sum(a, b)));
                } else 
                if (expression.at(i) == '-')
                {
                    _stack.push(to_string(difference(a, b)));
                } else
                if (expression.at(i) == '*')
                {
                    _stack.push(to_string(product(a, b)));
                } else
                if (expression.at(i) == '/')
                {
                    _stack.push(to_string(quotient(a, b)));
                } else
                if (expression.at(i) == '^')
                {
                    _stack.push(to_string(power(a, b)));
                }

            } else

            if (expression.at(i) == ';')
            {
                if (temp_operand.size() > 0)
                    _stack.push(temp_operand);
                temp_operand = ""; // Clear temp_operand string, reset it to "".
            } else 

            {
                temp_operand += expression.at(i);
            }
        }

        res = stod(_stack.top());
    }

    return res;
}