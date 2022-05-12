#ifndef _VALD_CHECK_H_
#define _VALD_CHECK_H_

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
                if (numH > 0) return "Error";
                else {
                    if (sign % 2 == 0) res += "";
                    else res += '-';
                }
            }
            else {
                if (numH >= 1 && num>=2) return "Error";  //
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
    if (isOperator(res[res.size() - 1])) return "Error";
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
    for (int i = 0; i < s.size()-1; i++) {
        if (isOperand(s.at(i)) && s.at(i + 1) == ' ') {
            int j = 1;
            while (s.at(i + j) == ' ') {
                j++;
            }
            if (isOperand(s.at(i + j))) {
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
    if (check == 0) return "Error";
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
                return "Error";
            }
            pos.pop();
        }
        return res;
    }
}
    
string to_post_fix(const string& s);
string to_pre_fix(const string& s);
double arithmetic_value(const string& expression, unsigned int _mode);

string checkOrder(const string& s) {
    if (s.compare("Error") == 0)  return "Error";
    double u, v;
    u = arithmetic_value(to_post_fix(s), 1);
    v = arithmetic_value(to_pre_fix(s), 0);
    if (u == v) return s;
    else return "Error";
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


#endif
