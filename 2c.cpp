#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isOperator(char c)
{
    if (c == '&' || c == '|' || c == '!' || c == '>' || c == '+')
        return true;
    return false;
}
bool isVariable(char c) {
    if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Conjunction(bool a, bool b)
{
    if (a == 1 && b == 1) { return 1; }
    else { return 0; }
}
bool Disjunction(bool a, bool b)
{
    if (a == 0 && b == 0) { return 0; }
    else { return 1; }
}
bool Implication(bool a, bool b)
{
    if (a == 1 && b == 0) { return 0; }
    else { return 1; }
}
bool Negation(bool a)
{
    if (a == 0) { return 1; }
    else { return 0; }
}
bool Exclusive_or(bool a, bool b)
{
    if (a == b) { return 0; }
    else { return 1; }
}

//Get variable's value
void getValue(string s) {

}
/**
 *  Convention:
 *      _mode
 *          = 0 : evaluate prefix string
 *          = 1 : evaluate postfix string
*/
double logical_value(string expression, unsigned int _mode)
{
        double res = 0;
        stack<string> _stack;
        string temp_operand = "";
        string new_expression = "";
        int size = 0;
        char* variable = new char[size];
        int* value = new int[size];
        for (unsigned int i = 0; i < expression.size(); i++) {
            if (isVariable(expression.at(i))) {
                bool check = 1;
                for (int j = 0; j < size; j++) {
                    if (expression.at(i) == variable[j]) { check = 0; break; }
                }
                if (check == 1) {
                    variable[size] = expression.at(i);
                    size++;
                }
            }
        }
        for (int i = 0; i < size; i++) {
            cout << variable[i] << ": ";
            cin >> value[i];
        }
        for (unsigned int i = 0; i < expression.size(); i++) {
            bool check = 0;
            for (int j = 0; j < size; j++) {
                if (expression.at(i) == variable[j]) {
                    new_expression += to_string(value[j]);
                    check = 1;
                    break;
                }
            }
            if (check == 0) { new_expression += expression.at(i); }
        }

        if (_mode == 0)
        {
            for (int i = new_expression.size() - 1; i >= 0; i--)
            {
                if (isOperator(new_expression.at(i)))
                {
                    if (_stack.size() >= 2 && new_expression.at(i) != '!') {
                        // Getting two top operands
                        double b = stoi(_stack.top());
                        _stack.pop();
                        double a = stoi(_stack.top());
                        _stack.pop();

                        // Evaluate & push it back to _stack
                        // double res : also updated accordingly
                        if (new_expression.at(i) == '&')
                        {
                            _stack.push(to_string(Conjunction(b, a)));
                        }
                        else
                            if (new_expression.at(i) == '|')
                            {
                                _stack.push(to_string(Disjunction(b, a)));
                            }
                            else
                                if (new_expression.at(i) == '>')
                                {
                                    _stack.push(to_string(Implication(b, a)));
                                }
                                else
                                    if (new_expression.at(i) == '+')
                                    {
                                        _stack.push(to_string(Exclusive_or(b, a)));
                                    }
                    }
                    if (new_expression.at(i) == '!')
                    {
                        double a = stoi(_stack.top());
                        _stack.pop();
                        _stack.push(to_string(Negation(a)));
                    }

                }
                else
                    if (new_expression.at(i) == ';')
                    {
                        if (temp_operand.size() > 0)
                            _stack.push(temp_operand);
                        temp_operand = ""; // Clear temp_operand string, reset it to "".
                    }
                    else

                    {
                        temp_operand += new_expression.at(i);
                    }
            }

            res = stoi(_stack.top());
        }
        if (_mode == 1)
        {
            for (unsigned int i = 0; i < new_expression.size(); i++)
            {
                if (isOperator(new_expression.at(i)))
                {
                    if (_stack.size() >= 2 && new_expression.at(i) != '!') {
                        // Getting two top operands
                        double b = stoi(_stack.top());
                        _stack.pop();
                        double a = stoi(_stack.top());
                        _stack.pop();

                        // Evaluate & push it back to _stack
                        // double res : also updated accordingly
                        if (new_expression.at(i) == '&')
                        {
                            _stack.push(to_string(Conjunction(a, b)));
                        }
                        else
                            if (new_expression.at(i) == '|')
                            {
                                _stack.push(to_string(Disjunction(a, b)));
                            }
                            else
                                if (new_expression.at(i) == '>')
                                {
                                    _stack.push(to_string(Implication(a, b)));
                                }
                                else
                                    if (new_expression.at(i) == '+')
                                    {
                                        _stack.push(to_string(Exclusive_or(a, b)));
                                    }
                    }
                    else
                        if (new_expression.at(i) == '!')
                        {
                            double a = stoi(_stack.top());
                            _stack.pop();
                            _stack.push(to_string(Negation(a)));
                        }

                }
                else

                    if (new_expression.at(i) == ';')
                    {
                        if (temp_operand.size() > 0)
                            _stack.push(temp_operand);
                        temp_operand = ""; // Clear temp_operand string, reset it to "".
                    }
                    else

                    {
                        temp_operand += new_expression.at(i);
                    }
            }

            res = stoi(_stack.top());
        }
        return res;
}
