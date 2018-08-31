#include <bits/stdc++.h>
#define ll long long
using namespace std;

void runningMedian(vector<double> a)
{
    priority_queue<double, vector<double>, greater<double>> left;
    priority_queue<double> right;
    vector<double> ans(a.size(), 0);
    right.push(a[0]);
    ans[0] = a[0];
    for (ll i = 1; i < a.size(); i++)
    {
        double element = a[i];
        if (right.size() == left.size())
        {
            if (ans[i - 1] > element)
            {
                right.push(element);
                ans[i] = right.top();
            }
            else
            {
                left.push(element);
                ans[i] = left.top() * 1.0;
            }
        }
        else if (right.size() > left.size())
        {
            if (element < ans[i - 1])
            {
                left.push(right.top());
                right.pop();
                right.push(element);
            }
            else
                left.push(element);

            ans[i] = (left.top() + right.top()) / 2.0;
        }
        else
        {
            if (element > ans[i - 1])
            {
                right.push(left.top());
                left.pop();
                left.push(element);
            }
            else
                right.push(element);

            ans[i] = (left.top() + right.top()) / 2.0;
        }
    }
    for (auto i : ans)
        cout << fixed << setprecision(1) << i << endl;
    return;
}

int main()
{
    ll n;
    cin >> n;
    vector<double> v(n);
    for (ll i = 0; i < n; i++)
        cin >> v[i];
    runningMedian(v);
    return 0;
}
