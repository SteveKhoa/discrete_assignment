/**
 *      DISCRETE STRUCTURES FOR COMPUTING ASSIGNMENT 212
 *
 *          Assignment: Evaluating expression.
            Discrete Structures for Computing (CO1007)
            Semester: 212 - Class: CC02 - Group: 7

                Group members:
                    1. Nguyen Huynh An - 2154018
                    2. Luong Le Long Vu - 2153980
                    3. Tran Gia Huy - 2152600
                    4. Le Tran Nguyen Khoa - 2152674

            NOTES:
        This file combines all the codes together.
 *      Please go to   'int main()'   and define     'expression'     to see the result.
*/

#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>

using namespace std;

bool isOperator(char c)
{
    if (c == '*' || c == '/' || c == '+' || c == '-' || c == '^')
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
    if (_stack_top == '^')
    {
        if (c == '*' || c == '/' || c == '+' || c == '-' || c == '^')
            return true;
    }
    else
        if (_stack_top == '*' || _stack_top == '/')
        {
            if (c == '+' || c == '-' || c == '*' || c == '/')
                return true;
        }
        else
            if (_stack_top == '+' || _stack_top == '-')
            {
                if (c == '+' || c == '-')
                    return true;
            }

    return false;
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


string to_pre_fix(const string& s)
{
    string res = "";
    stack<char> operators;

    // Operand is a special string that contains many characters (ex: 7894522)
    // bool start_operand : ensure that for loops entire "7894522" before adding ';'
    // bool start_operand is turned off : everytime the loop reaches non-operand characters.
    bool start_operand = 0;

    for (int i = s.size() - 1; i >= -1; i--)
    {
        if (i == -1)
        {
            while (!operators.empty())
            {
                res += ';';
                res += operators.top();
                operators.pop();
            }
            break;
        }

        if (isBracket(s.at(i)))
        {
            start_operand = 0;
            if (isOpenBracket(s.at(i)))
            {
                while (!operators.empty() && !isOpened(s.at(i), operators.top()))
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
                    if (i != s.size() - 1)
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
                            res += ';';
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

    reverse_string(res);

    return res;
}

string to_post_fix(const string& s)
{
    //--- must check validity of the string s here ---//

    // Note: Seperate the elements with ';'

    // Note: The code below assumes that the input string has correct syntax

    string res = "";
    stack<char> operators;

    // Operand is a special string that contains many characters (ex: 7894522)
    // bool start_operand : ensure that for loops entire "7894522" before adding ';'
    // bool start_operand is turned off : everytime the loop reaches non-operand characters.
    bool start_operand = 0;

    for (unsigned int i = 0; i <= s.size(); i++)
    {
        if (i == s.size())
        {
            while (!operators.empty())
            {
                res += ';';
                res += operators.top();
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
                    if (i != 0)
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
                            res += ';';
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
double arithmetic_value(const string& expression, unsigned int _mode)
{
    double res = 0;
    string temp_operand = "";
    stack<string> _stack;

    // prefix evaluation
    if (_mode == 0)
    {
        for (int i = expression.size() - 1; i >= 0; --i)
        {
            if (_stack.size() >= 2 && isOperator(expression.at(i)))
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
                }
                else
                    if (expression.at(i) == '-')
                    {
                        _stack.push(to_string(difference(a, b)));
                    }
                    else
                        if (expression.at(i) == '*')
                        {
                            _stack.push(to_string(product(a, b)));
                        }
                        else
                            if (expression.at(i) == '/')
                            {
                                _stack.push(to_string(quotient(a, b)));
                            }
                            else
                                if (expression.at(i) == '^')
                                {
                                    _stack.push(to_string(power(a, b)));
                                }

            }
            else

                if (expression.at(i) == ';')
                {
                    if (temp_operand.size() > 0)
                        _stack.push(temp_operand);
                    temp_operand = ""; // Clear temp_operand string, reset it to "".
                }
                else

                {
                    temp_operand.insert(0, 1, expression.at(i));
                }
        }

        res = stod(_stack.top());
    }
    else

        // postfix evaluation
        if (_mode == 1)
        {
            for (unsigned int i = 0; i < expression.size(); ++i)
            {
                if (_stack.size() >= 2 && isOperator(expression.at(i)))
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
                    }
                    else
                        if (expression.at(i) == '-')
                        {
                            _stack.push(to_string(difference(a, b)));
                        }
                        else
                            if (expression.at(i) == '*')
                            {
                                _stack.push(to_string(product(a, b)));
                            }
                            else
                                if (expression.at(i) == '/')
                                {
                                    _stack.push(to_string(quotient(a, b)));
                                }
                                else
                                    if (expression.at(i) == '^')
                                    {
                                        _stack.push(to_string(power(a, b)));
                                    }

                }
                else

                    if (expression.at(i) == ';')
                    {
                        if (temp_operand.size() > 0)
                            _stack.push(temp_operand);
                        temp_operand = ""; // Clear temp_operand string, reset it to "".
                    }
                    else

                    {
                        temp_operand += expression.at(i);
                    }
            }

            res = stod(_stack.top());
        }

    return res;
}

string checkConsecutiveOperators(const string& s) {
    string res = "";
    if (s.compare("Error") == 0)  return "Error";
    for (unsigned int i = 0; i < s.size(); i++) {
        if (isOperator(s[i])) {
            int num = 0, sign = 0, numH = 0, pos;
            int index = i;
            while (isOperator(s[index])) {
                index++;
                num++;
            }
            for (int j = i; j < i + num; j++) {
                if (s[j] == '+')  sign += 2;
                if (s[j] == '-')  sign += 1;
                if (s[j] == '*' || s[j] == '^' || s[j] == '/') {
                    numH++;
                    pos = j;
                }
            }
            if (i == 0) {
                if (numH > 0) { cout << "Undefined error!" << "\n"; return "Error";}
                else {
                    if (sign % 2 == 0) res += "";
                    else res += '-';
                }
            }
            else {
                if (numH >= 1 && num>=2) { cout << "Undefined error!" << "\n"; return "Error";}//
                else if (numH == 1 && num == 1) {
                    res += s.at(i);
                }
                else  {
                    if (sign % 2 == 0) res += '+';
                    else res += '-';
                }
            }
            i += num - 1;
        }
        else res += s.at(i);
    }
    if (isOperator(res[res.size() - 1])) { cout << "Undefined error!" << "\n"; return "Error"; }
    return res;
}

string checkFloatingPoint(const string& s) {
    string res;
    if (s.compare("Error") == 0)  return "Error";
    int check = 1;
    int l = s.size();
    if (s[0] == '.' || s[l - 1] == '.') return "Error";
    for (int i = 1; i < l - 1; i++) {
        if (s[i] == '.') {
            if (isOperand(s[i - 1]) == 0 || isOperand(s[i + 1]) == 0) {
                cout << "Syntax error!" << "\n";
                return "Error";
            }
            else res += s.at(i);
        }
        else res += s.at(i);
    }
    return s;
}

string checkBlank(const string& s) {
    string res;
    if (s.compare("Error") == 0)  return "Error";
    for (int i = 0; i < s.size() - 1; i++) {
        if (isOperand(s.at(i)) && s.at(i + 1) == ' ') {
            int j = 1;
            while (s.at(i + j) == ' ') {
                j++;
            }
            if (isOperand(s.at(i + j))) {
                cout << "Syntax error!" << "\n";
                return "Error";
            }
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == ' ') continue;
        else res += s.at(i);
    }
    return res;
}

bool isOpenBracket(char c);
string checkParenthesis(const string& s) {
    // Check whether open brackets match with closed brackets or not
    if (s.compare("Error") == 0)  return "Error";
    string res;
    stack<char> bracket;
    stack<int> pos; //position of open bracket
    bool check = true;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (isOpenBracket(s[i])) {
            bracket.push(s.at(i));
            pos.push(i);
        }
        else if (isClosedBracket(s[i])) {
            if (bracket.empty()) {
                check = 0;
                break;
            }
            else if (bracket.size() > 0) {
                if (!isEnclosed(s.at(i), bracket.top())) {
                    check = 0;
                    break;
                }
                else {
                    bracket.pop();
                }
            }
        }
        else continue;
    }
    if (check == 0) 
    {
        cout << "Syntax error!" << "\n";
        return "Error";
    }
    else {   //eliminate brackets that do not have operand inside
        for (int i = 0; i < s.size(); i++) {
            res += s.at(i);
        }
        while (!pos.empty()) {
            if (isClosedBracket(res[pos.top() + 1])) {
                res[pos.top() + 1] = 0;
                res[pos.top()] = 0;
            }
            if (isOperator(res[pos.top() + 1])) {
                cout << "Syntax error!" << "\n";
                return "Error";
            }
            pos.pop();
        }
        return res;
    }
}

string checkOrder(const string& s) {
    if (s.compare("Error") == 0)  return "Error";
    double u, v;
    u = arithmetic_value(to_post_fix(s), 1);
    v = arithmetic_value(to_pre_fix(s), 0);
    if (u == v) return s;
    else 
    {
        cout << "Multiple output error!" << "\n";
        return "Error";
    }
}

void checkValidity(const string& s, string& checkedS) {
    for (int i = 0; i < s.size(); i++) {
        checkedS += s.at(i);
    }
    checkedS = checkBlank(checkedS);
    checkedS = checkConsecutiveOperators(checkedS);
    checkedS = checkFloatingPoint(checkedS);
    checkedS = checkParenthesis(checkedS);
    checkedS = checkOrder(checkedS);
}


//----------Exercise2-----------

bool isOperator_2(char c)
{
    if (c == '&' || c == '|' || c == '!' || c == '>' || c == '+')
        return true;
    return false;
}

bool morePrior_2(char _stack_top, char c)
{
    if (_stack_top == '!')
    {
        if (c == '+' || c == '>' || c == '&' || c == '|')
            return true;
    }
    else
        if (_stack_top == '+' || _stack_top == '&' || _stack_top == '|')
        {
            if (c == '+' || c == '>' || c == '&' || c == '|')
                return true;
        }
        else
            if (_stack_top == '>')
            {
                if (c == '>')
                    return true;
            }

    return false;
}

//Check validity
bool checkOperators_2(const string& s) {
    bool check = 1;
    for (unsigned int i = 0; i < s.size() - 1; i++) {
        if (isOperator(s.at(i)) && isOperator(s.at(i + 1))) {
            if (s.at(i + 1) != '!') { check = 0; break; }
        }
    }
    return check;
}

bool checkOrder_2(const string& s) {
    bool check = 1;
    for (unsigned int i = 0; i < s.size() - 2; i++) {
        if (s.at(i) == '&' || s.at(i) == '|' || s.at(i) == '+') {
            if ((s.at(i + 2) == '&' || s.at(i + 2) == '|' || s.at(i + 2) == '+') && s.at(i + 2) != s.at(i)) {
                check = 0;
                break;
            }
        }
    }
    return check;
}

bool checkParenthesis_2(const string& s) {
    bool check = 1;
    int open = 0, close = 0;
    for (unsigned int i = 0; i < s.size() - 2; i++) {
        if (isOpenBracket(s.at(i))) {
            if (isClosedBracket(s.at(i + 2)) && isOperator(s.at(i + 1))) {
                check = 0;
                break;
            }
            else if (isOperator(s.at(i + 1)) && s.at(i + 1) != '!') {
                check = 0;
                break;
            }
        }
    }
    for (unsigned int i = 1; i < s.size(); i++) {
        if (isClosedBracket(s.at(i))) {
            if (isOperator(s.at(i - 1))) { check = 0; break; }
        }
    }
    if (check == 1) {
        for (unsigned int i = 0; i < s.size(); i++) {
            if (isOpenBracket(s.at(i))) {
                open++;
            }
            if (isClosedBracket(s.at(i))) {
                close++;
            }
            if (close > open) { check = 0; break; }
        }
        if (close != open) { check = 0; }
    }
    return check;
}

bool checkBlank_2(const string& s) {
    bool check = 1;
    for (unsigned int i = 0; i < s.size() - 1; i++) {
        if (isOperand(s.at(i)) && s.at(i + 1) == ' ') {
            int j = 1;
            while (s.at(i + j) == ' ') {
                j++;
            }
            if (isOperand(s.at(i + j))) { check = 0; break; }
        }
    }
    if (check == 1) {
        string s1;
        for (unsigned int i = 0; i < s.size(); i++) {
            if (s.at(i) != ' ') {
                s1 += s.at(i);
            }
        }
        if (!checkOperators_2(s1) || !checkOrder_2(s1) || !checkParenthesis_2(s1)) { check = 0; }
    }
    return check;
}

void checkValidity_2(const string &expression, string &s) {
    if (checkOperators_2(expression) && checkOrder_2(expression) && checkParenthesis_2(expression) && checkBlank_2(expression)) { s = expression; }
    else { s = "Error"; }
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

//Part 1: Prefix
string to_pre_fix_2(string s)
{
        string res = "";
        stack<char> operators;
        // Operand is a special string that contains many characters (ex: 7894522)
        // bool start_operand : ensure that for loops entire "7894522" before adding ';'
        // bool start_operand is turned off : everytime the loop reaches non-operand characters.
        bool start_operand = 0;
        s = new_string(s);
        for (int i = s.size() - 1; i >= -1; i--)
        {
            if (i == -1)
            {
                while (!operators.empty())
                {
                    res += ';';
                    res += operators.top();
                    operators.pop();
                }
                break;
            }

            if (isBracket(s.at(i)))
            {
                start_operand = 0;
                if (isOpenBracket(s.at(i)))
                {
                    while (!operators.empty() && !isOpened(s.at(i), operators.top()))
                    {
                        res += ';';
                        res += operators.top();
                        operators.pop();
                    }
                    if (!operators.empty()) { operators.pop(); }
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
                        if (i != s.size() - 1 && res != "")
                            res += ';';
                    }

                    res += s.at(i);
                }
                else

                    if (isOperator_2(s.at(i)))
                    {
                        start_operand = 0;
                        if (!operators.empty() && morePrior(operators.top(), s.at(i)))
                        {
                            while (!operators.empty() && morePrior(operators.top(), s.at(i)))
                            {
                                res += ';';
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
        reverse_string(res);
        return res;

}

//Part 2: Postfix
string to_post_fix_2(string s)
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

                    if (isOperator_2(s.at(i)))
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

//Part3 
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
        
        // Getting value of variables
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
                if (isOperator_2(new_expression.at(i)))
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
                if (isOperator_2(new_expression.at(i)))
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



int main()
{
    /**
     * 
     *      Notes:
     *          1. expression : for arithmetic expression
     *          2. expression_2 : for logical value
     *          
     *          3. For logical expression, when symbolic variables (p q a r ...)
     *          are used, we must type in a boolean value (0 or 1), so that
     *          the result can be returned approriately.
    */
    const string expression = "2//3"; // Change the arithmetic expression for testing
    const string expression_2 = "1&1&1"; // Change the logical expression for testing

    cout << "..........................................\n";
    cout << "Original arithmetic: " << expression << "\n";
    string s = "";
    checkValidity(expression, s);
    if (s.compare("Error") == 0) cout << ">> The input is invalid\n";
    else {
        cout << "--------------------- \n";
        cout << "Postfix: " << to_post_fix(s) << "\n";
        cout << "Postfix value: " << arithmetic_value(to_post_fix(s), 1) << "\n";
        cout << "\n";
        cout << "Prefix: " << to_pre_fix(s) << "\n";
        cout << "Prefix value: " << arithmetic_value(to_pre_fix(s), 0) << "\n";
    }
    cout << "**********************************\n";

    cout << "Original logical: " << expression_2 << "\n";
    string s2 = "";
    checkValidity_2(expression_2, s2);
    if (s2.compare("Error") == 0) cout << ">> The input is invalid\n";
    else {
        cout << "--------------------- \n";
        cout << "Postfix: " << to_post_fix_2(s2) << "\n";
        cout << "Postfix value: " << logical_value(to_post_fix_2(s2), 1) << "\n";
        cout << "\n";
        cout << "Prefix: " << to_pre_fix_2(s2) << "\n";
        cout << "Prefix value: " << logical_value(to_pre_fix_2(s2), 0) << "\n";
    }
    cout << "..........................................\n";
    return 0;
}
