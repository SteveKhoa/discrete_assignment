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

bool isOperand(char c)
{
    if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isBracket(char c)
{
    if
        (
            c == '(' || c == ')' ||
            c == '[' || c == ']' ||
            c == '{' || c == '}'
            )
        return true;

    return false;

}

bool isClosedBracket(char c)
{
    if (c == ')' || c == ']' || c == '}')
        return true;

    return false;
}

bool morePrior(char _stack_top, char c)
{
    if (_stack_top == '!')
    {
        if (c == '+' || c == '>' || c == '&' || c == '|'){ return true; }
        else { return false; }
    }
    else
        if (_stack_top == '+' || _stack_top == '&' || _stack_top == '|')
        {
            if (c == '+' || c == '>' || c == '&' || c == '|'){ return true; }
            else { return false; }
        }
        else
            if (_stack_top == '>')
            {
                if (c == '>'){ return true; }
                else { return false; }
            }
}

char mapToClosedBracket(char c)
{
    if (c == '(')
        return ')';
    if (c == '[')
        return ']';
    if (c == '{')
        return '}';

    // Return '_' unknown if does not match any bracket.
    return '_';
}

bool isEnclosed(char _close_bracket, char _stack_top)
{
    if (_close_bracket == mapToClosedBracket(_stack_top))
        return true;

    return false;
}

bool isOpenBracket(char c)
{
    if (c == '(' || c == '[' || c == '{')
        return true;

    return false;
}

char mapToOpenBracket(char c)
{
    if (c == ')')
        return '(';
    if (c == ']')
        return '[';
    if (c == '}')
        return '{';

    // Return '_' unknown if does not match any bracket.
    return '_';
}

bool isOpened(char _open_bracket, char _stack_top)
{
    if (_open_bracket == mapToOpenBracket(_stack_top))
        return true;

    return false;
}

void reverse_string(string& s)
{
    string res = "";
    for (int i = s.size() - 1; i >= 0; i--)
    {
        res += s.at(i);
    }

    s = res;
}


//Proposition
string new_string(string s) {
    string s1 = "";
    for (unsigned int i = 0; i < s.size() - 1; i++) {
        if (isOperand(s.at(i)) && isOperand(s.at(i + 1))) {
            s1 += s.at(i);
            s1 += "&";
        }
        else { s1 += s.at(i); }
    }
    s1 += s.at(s.size() - 1);
    return s1;
}

string to_post_fix(string s)
{
        // Note: Seperate the elements with ';'

    // Note: The code below assumes that the input string has correct syntax

        string res = "";
        stack<char> operators;

        // Operand is a special string that contains many characters (ex: 7894522)
        // bool start_operand : ensure that for loops entire "7894522" before adding ';'
        // bool start_operand is turned off : everytime the loop reaches non-operand characters.
        bool start_operand = 0;
        s = new_string(s);
        for (unsigned int i = 0; i <= s.size(); i++)
        {
            if (i == s.size())
            {
                while (!operators.empty())
                {
                    if (!isBracket(operators.top())) {
                        res += ';';
                        res += operators.top();
                    }
                    operators.pop();
                }
                break;
            }

            if (isBracket(s.at(i)))
            {
                start_operand = 0;
                if (isClosedBracket(s.at(i)))
                {
                    while (!operators.empty() && !isEnclosed(s.at(i), operators.top()))
                    {
                        res += ';';
                        res += operators.top();
                        operators.pop();
                    }

                    operators.pop();
                }
                else
                {
                    operators.push(s.at(i));
                }
            }
            else

                if (isOperand(s.at(i)))
                {
                    if (!start_operand)
                    {
                        start_operand = 1;
                        if (i != 0 && res != "")
                            res += ';';
                    }

                    res += s.at(i);
                }
                else

                    if (isOperator(s.at(i)))
                    {
                        start_operand = 0;
                        if (!operators.empty() && morePrior(operators.top(), s.at(i)))
                        {
                            while (!operators.empty() && morePrior(operators.top(), s.at(i)))
                            {
                                if (res != "") { res += ';'; }
                                res += operators.top();
                                operators.pop();
                            }

                            operators.push(s.at(i));
                        }
                        else
                        {
                            operators.push(s.at(i));
                        }
                    }
        }

        return res;
}
