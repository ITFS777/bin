#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using number_t = long double;
enum tokenType
{
    UNKNOWN,
    NUMBER,
    OPERATOR,
    VARIABLE
};
class Token
{
public:
    Token() = default;
    Token(tokenType _Type, string _Val) : type(_Type), val(_Val) {}

    tokenType type;
    string val;
};
class OperatorPrior
{
public:
    OperatorPrior() = default;
    OperatorPrior(char _Symbol, int _InStackPrior, int _InComingPrior) : symb(_Symbol), isp(_InStackPrior), icp(_InComingPrior) {}

    char symb;
    int isp;
    int icp;
};
// The operator below should be same with the switch body in line 56
const std::vector<char>
    OPERATOR_LIST = {
        '+', '-', '*', '/', '^', '='};
const std::vector<OperatorPrior> PRIORITY_LIST = {
    OperatorPrior('#', -1, -1),
    // OperatorPrior('=', 1, 0),
    OperatorPrior('+', 3, 2),
    OperatorPrior('-', 3, 2),
    OperatorPrior('*', 5, 4),
    OperatorPrior('/', 5, 4),
    OperatorPrior('^', 7, 6),
    OperatorPrior('(', 1, 127),
    OperatorPrior(')', 127, 1)};
int icp(char _Symbol);
int isp(char _Symbol);
int typeMatch(const char &_TokenHead);
template <typename ElementType>
bool isIn(const std::vector<ElementType> &_Container, const ElementType &_Element);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // Initialize containers
    std::map<string, number_t> vars;
    std::stack<number_t> num_stack;
    std::vector<Token> expr_anay;
    string expression, token, assigned;
    number_t left_val, right_val, result;
    bool is_assign = false;

    // Process and calculate
    while (true)
    {
        // Convert mid_expression to back_expression
        is_assign = false;
        std::stack<char> symbs;
        symbs.push('#');
        expression.clear();
        token.clear();
        assigned.clear();
        expr_anay.clear();
        getline(cin, expression);
        for (auto i = expression.begin(); i != expression.end(); ++i)
        {
            token.clear();
            switch (typeMatch(*i))
            {
            case NUMBER:
                token += *i++;
                while ((*i >= '0' && *i <= '9') || (*i == '.'))
                    token += *i++;
                expr_anay.push_back(Token(NUMBER, token));
                --i;
                break;
            case OPERATOR:
                if (*i == '=')
                {
                    is_assign = true;
                    assigned = expr_anay.back().val;
                    expr_anay.pop_back();
                    break;
                }
                if (icp(*i) > isp(symbs.top()))
                    symbs.push(*i);
                else if (icp(*i) < isp(symbs.top()))
                {
                    expr_anay.push_back(Token(OPERATOR, string(1, symbs.top())));
                    symbs.pop();
                    symbs.push(*i);
                }
                else
                    symbs.pop();
                break;
            case VARIABLE:
                token += *i++;
                while ((*i >= 'a' && *i <= 'z') || (*i >= 'A' && *i <= 'Z') || (*i >= '0' && *i <= '9') || (*i == '_'))
                    token += *i++;
                expr_anay.push_back(Token(VARIABLE, token));
                --i;
                break;
            default:
                break;
            }
        }
        while (symbs.top() != '#')
        {
            expr_anay.push_back(Token(OPERATOR, string(1, symbs.top())));
            symbs.pop();
        }

        ///////////////////////////////////DEBUG INFO///////////////////////////////////
/* 
        cout << "------------------------------------------------------------" << endl;
        cout << expr_anay.size() << endl;
        for (auto i = expr_anay.begin(); i != expr_anay.end(); ++i)
            cout << i->type << ' ' << i->val << endl;
        cout << "------------------------------------------------------------" << endl;
 */
        ////////////////////////////////////////////////////////////////////////////////

        // Calculate
        while (!num_stack.empty())
            num_stack.pop();
        for (auto i = expr_anay.begin(); i != expr_anay.end(); ++i)
        {
            switch (i->type)
            {
            case NUMBER:
                num_stack.push(stold(i->val));
                break;
            case VARIABLE:
                num_stack.push(vars[i->val]);
                break;
            case OPERATOR:
                right_val = num_stack.top();
                num_stack.pop();
                left_val = num_stack.top();
                num_stack.pop();
                switch (i->val[0])
                {
                case '+':
                    result = left_val + right_val;
                    break;
                case '-':
                    result = left_val - right_val;
                    break;
                case '*':
                    result = left_val * right_val;
                    break;
                case '/':
                    result = left_val / right_val;
                    break;
                case '^':
                    result = pow(left_val, right_val);
                    break;
                default:
                    break;
                }
                num_stack.push(result);
                break;
            default:
                break;
            }
        }

        // Output
        if (num_stack.size() == 1)
        {
            if (is_assign)
                vars[assigned] = num_stack.top();
            else
                cout << "result: " << num_stack.top() << endl;
        }
        else
            cout << "Illegal input!" << endl;
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
int icp(char _Symbol)
{
    for (auto i = PRIORITY_LIST.begin(); i != PRIORITY_LIST.end(); ++i)
        if (_Symbol == i->symb)
            return i->icp;
    return -1;
}
int isp(char _Symbol)
{
    for (auto i = PRIORITY_LIST.begin(); i != PRIORITY_LIST.end(); ++i)
        if (_Symbol == i->symb)
            return i->isp;
    return -1;
}
////////////////////////////////////////////////////////////////////////////////
int typeMatch(const char &_TokenHead)
{
    if (_TokenHead >= '0' && _TokenHead <= '9')
        return NUMBER;
    else if (isIn(OPERATOR_LIST, _TokenHead))
        return OPERATOR;
    else if ((_TokenHead >= 'a' && _TokenHead <= 'z') || (_TokenHead >= 'A' && _TokenHead <= 'Z') || (_TokenHead == '_'))
        return VARIABLE;
    else
        return UNKNOWN;
}
////////////////////////////////////////////////////////////////////////////////
template <typename ElementType>
bool isIn(const std::vector<ElementType> &_Container, const ElementType &_Element)
{
    for (auto i = _Container.begin(); i != _Container.end(); ++i)
        if (_Element == *i)
            return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////