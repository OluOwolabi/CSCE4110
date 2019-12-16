#include <utility>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define MOD 1000000007
#define INF 1000000000
#define pb push_back
#define sz size()
#define mp make_pair

int knapsack(int value[], int weight[], int n_items, int maixumWeight)
{
    int dp[n_items + 1][maixumWeight + 1];

    for (int w = 0; w <= maixumWeight; w++)
        dp[0][w] = 0;

    for (int i = 0; i <= n_items; i++)
        dp[i][0] = 0;

    for (int i = 1; i <= n_items; i++)
        for (int w = 1; w <= maixumWeight; w++)
        {
            if (weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }

    return dp[n_items][maixumWeight];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int value[] = {50, 25, 60, 15, 40, 30, 50, 30, 50, 10};
    int weight[] = {3, 2, 4, 1, 3, 2, 3, 2, 4, 1};
    int n_tems = 10;
    int maixumWeight = 10;

    cout << knapsack(value, weight, n_tems, maixumWeight) << endl;    //values of the items, weights, number of items and the maximum weight
    return 0;
}