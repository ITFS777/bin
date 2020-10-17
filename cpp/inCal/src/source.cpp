#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
// #define DEBUG
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
        '+', '-', '*', '/', '^', '=', '(', ')'};
const std::vector<OperatorPrior> PRIORITY_LIST = {
    OperatorPrior('#', -1, -1),
    OperatorPrior('+', 3, 2),
    OperatorPrior('-', 3, 2),
    OperatorPrior('*', 5, 4),
    OperatorPrior('/', 5, 4),
    OperatorPrior('^', 7, 6),
    OperatorPrior('(', 1, 127),
    OperatorPrior(')', 127, 1)};
std::map<string, number_t> g_vars;
int icp(char _Symbol);
int isp(char _Symbol);
int typeMatch(const char &_TokenHead);
template <typename ElementType>
bool isIn(const std::vector<ElementType> &_Container, const ElementType &_Element);
number_t calculate(std::vector<Token> &_TokenStack);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // Initialize containers
    std::vector<Token> expr_anay;
    string expression, token, assigned;
    number_t result;
    bool is_assign = false;
    int num_c, symb_c, lbracket_c, rbracket_c;
    // Process and calculate
    while (true)
    {
        // Convert mid_expression to back_expression
        is_assign = false;
        num_c = 0;
        symb_c = 0;
        lbracket_c = 0;
        rbracket_c = 0;
        std::stack<char> symbs;
        symbs.push('#');
        expression.clear();
        token.clear();
        assigned.clear();
        expr_anay.clear();
        getline(cin, expression);
        try
        {
#ifdef DEBUG // STACK INFO

            for (auto i = expr_anay.begin(); i != expr_anay.end(); ++i)
                cout << i->val << ' ';
            cout << endl;

#endif
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
                    ++num_c;
                    break;
                case OPERATOR:
                    // Assignment expression
                    if (*i == '=')
                    {
                        if (expr_anay.size() == 1)
                        {
                            if (expr_anay.back().type == VARIABLE)
                            {
                                is_assign = true;
                                assigned = expr_anay.back().val;
                                expr_anay.pop_back();
                                --num_c;
                                break;
                            }
                            else
                                throw std::runtime_error("It can only be variable on the left of '='.");
                        }
                        else
                            throw std::runtime_error("There should be only one variable on the left of '='.");
                    }

                    // Value expression
                    else if (icp(*i) > isp(symbs.top()))
                    {
                        if (*i == '(')
                            ++lbracket_c;
                        if (*i == ')')
                            ++rbracket_c;
                        symbs.push(*i);
                    }
                    else
                    {
                        if (*i == ')')
                            ++rbracket_c;
                        while (icp(*i) < isp(symbs.top()))
                        {

                            expr_anay.push_back(Token(OPERATOR, string(1, symbs.top())));
                            symbs.pop();
                        }

                        // Bracket match
                        if (icp(*i) == isp(symbs.top()))
                        {
                            symbs.pop();
                            --lbracket_c;
                            --rbracket_c;
                        }
                        else
                            symbs.push(*i);
                    }
                    if (*i != '(' && *i != ')')
                        ++symb_c;
                    break;
                case VARIABLE:
                    token += *i++;
                    while ((*i >= 'a' && *i <= 'z') || (*i >= 'A' && *i <= 'Z') || (*i >= '0' && *i <= '9') || (*i == '_'))
                        token += *i++;
                    expr_anay.push_back(Token(VARIABLE, token));
                    --i;
                    ++num_c;
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
#ifdef DEBUG // STACK INFO

            cout << "------------------------------------------------------------" << endl;
            cout << expr_anay.size() << endl;
            for (auto i = expr_anay.begin(); i != expr_anay.end(); ++i)
                cout << i->type << ' ' << i->val << endl;
            cout << "------------------------------------------------------------" << endl;

#endif
            // Error detection
            if ((num_c - 1) > symb_c)
                throw std::runtime_error("Overmuch number(s) or variable(s).");
            if ((num_c - 1) < symb_c)
                throw std::runtime_error("Overmuch operator(s).");
            if (lbracket_c > rbracket_c)
                throw std::runtime_error("More open '(' bracket(s) than closed ')' bracket(s).");
            if (lbracket_c < rbracket_c)
                throw std::runtime_error("More closed ')' bracket(s) than open '(' bracket(s).");

            // Calculate
            result = calculate(expr_anay);

            // Output
            if (is_assign)
                g_vars[assigned] = result;
            else
                cout << "ans = " << result << endl;
        }
        catch (std::runtime_error &err)
        { // Output error info
            std::cerr << "ERROR: " << err.what() << endl;
        }
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
number_t calculate(std::vector<Token> &_TokenStack)
{
    std::stack<number_t> num_stack;
    number_t left_val, right_val, result;
    for (auto i = _TokenStack.begin(); i != _TokenStack.end(); ++i)
    {
        switch (i->type)
        {
        case NUMBER:
            num_stack.push(stold(i->val));
            break;
        case VARIABLE:
            num_stack.push(g_vars[i->val]);
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
    return num_stack.top();
}