#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <cmath>
#include <map>
#include <set>
#define NUM 1000000007
//#define ll long long
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
#define int long long
using namespace std;
int f(int n)
{
    int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        fact = (fact * i) % NUM;
    }
    return fact;
}
//isPrime function taken from https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}
int pow(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
int invmod(int a, int m)
{
    return pow(a, m - 2, m);
}
int binomialCoeff(int n, int r)
{
    if (n < r)
        return 0;
    return (f(n) * invmod(f(r), NUM) % NUM * invmod(f(n - r), NUM) % NUM) % NUM;
}
void sieve(int n, vector<int> &primes)
{
    vector<int> mark(n + 1);
    int p = 2;
    while (p * p <= n)
    {
        int i = p * p;
        while (i <= n)
        {
            mark[i] = 1;
            i += p;
        }
        int newp = p + 1;
        while (newp <= n && mark[newp])
        {
            newp++;
        }
        p = newp;
    }
    for (int i = 2; i <= n; i++)
    {
        if (!mark[i])
        {
            primes.push_back(i);
        }
    }
}
vector<int> kmp(string &text, string pat)
{
    vector<int> search;
    int n = pat.length();
    vector<int> lps(n);
    lps[0] = 0;
    int len = 0;
    for (int i = 1; i < n; i++)
    {
        if (pat[i] == pat[len])
        {
            lps[i] = (++len);
        }
        else if (pat[i] != pat[len])
        {
            len = 0;
            lps[i] = 0; //vaise bhee hai hee
        }
    }
    reverse(lps.begin(), lps.end());
    lps.push_back(0);
    reverse(lps.begin(), lps.end());
    reverse(pat.begin(), pat.end());
    pat.push_back('0');
    reverse(pat.begin(), pat.end());
    int j = 0;
    int i = 0;
    int start = 0;
    while (i < text.length())
    {
        if (pat[j + 1] == text[i])
        {
            i++;
            j++;
            if (j == n)
            {
                search.push_back(start + 1);

                j = lps[j];
                start = i - j;
            }
        }
        else
        {
            if (j == 0)
            {
                i++;
                start = i;
                continue;
            }
            j = lps[j];
            start = i - j;
        }
    }
    return search;
}
signed main()
{
    fio;
    int t{};
    cin >> t;
    while (t--)
    {
        string text, pat;
        cin >> text >> pat;
        vector<int> pos = kmp(text, pat);
        for (int i = 0; i < pos.size(); i++)
        {
            cout << pos[i] << " ";
        }
        cout << "\n";
    }
}
