#include <iostream>
#include <vector>
#include <cmath>
//////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::vector;
//////////////////////////////////////////////////////////////////////////
bool isPrime(long long int num)
{ /* 判断给定整数是否是素数,需包含math.h */
    int i = 0;
    if ((num == 2) || (num == 3))
        return true;
    if ((num % 6 != 1) && (num % 6 != 5))
        return false;
    for (i = 2; i <= sqrt(num); ++i)
    {
        if (num % i == 0)
            return false;
        else
            continue;
    }
    return true;
}
void numBreak(vector<long long int> &result, long long int target)
{
    int i = 2;
    while (i <= target)
    {
        if (isPrime(target))
        {
            result.push_back(target);
            break;
        }
        else
            while (i <= target)
                if (isPrime(i))
                {
                    if ((target % i) == 0)
                    {
                        result.push_back(i);
                        target /= i;
                        break;
                    }
                    else
                        ++i;
                }
                else
                    ++i;
    }
}
//////////////////////////////////////////////////////////////////////////
int main(void)
{
    long long int target = 0;
    int i = 0, length = 0;
    cout << "Number to break>";
    vector<long long int> result;
    while (cin >> target)
    {
        numBreak(result, target);
        length = result.size();
        cout << target << '=' << endl;
        for (i = 0; i < length; ++i)
            if (i)
                cout << " * " << result[i];
            else
                cout << result[i];
        cout << endl
             << "Number to break>";
        result.clear();
    }
    return 0;
}