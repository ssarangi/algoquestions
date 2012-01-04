/*
Given a list of N coins, their values (V1, V2, ... , VN), and the total sum S. Find the minimum number of coins the sum of which is S 
(we can use as many coins of one type as we want), or report that it's not possible to select coins in such a way that they sum up to S. 
*/

#include <iostream>
#include <vector>

using namespace std;

int minNumberOfCoins_approach1(vector<int>& coinValues, int sum)
{
    vector<int> iSums(sum + 1, INT_MAX);
    iSums[0] = 0;

    for (int i = 1; i <= sum; ++i)
    {
        for (unsigned int j = 0; j < coinValues.size(); j++)
        {
            int coin_val = coinValues[j];
            if (coin_val <= i && (iSums[i - coin_val] + 1) < iSums[i])
                iSums[i] = iSums[i - coin_val] + 1;
        }
    }

    return iSums[sum];
}

int minNumberOfCoins_approach2(vector<int>& coinValues, int sum)
{
    vector<int> iSums(sum + 1, INT_MAX);
    iSums[0] = 0;

    for (unsigned int j = 0; j < coinValues.size(); ++j)
    {
        for (int i = 0; i <= sum; i++)
        {
            int coin_val = coinValues[j];

            if (coin_val <= i && (iSums[i - coin_val] + 1) < iSums[i])
                iSums[i] = iSums[i - coin_val] + 1;
        }
    }

    return iSums[sum];
}

int main(void)
{
    int numValues;
    vector<int> coinValues;
    cout << "Enter number of values: ";
    cin >> numValues;

    cout << "Enter the values: " << endl;
    for (int i = 0; i < numValues; ++i)
    {
        int val;
        cin >> val;
        coinValues.push_back(val);
    }

    cout << "Sum: ";
    int sum;
    cin >> sum;

    int minCoins_approach1 = minNumberOfCoins_approach1(coinValues, sum);
    int minCoins_approach2 = minNumberOfCoins_approach2(coinValues, sum);

    cout << "Minimum Number of Coins (Approach 1): " << minCoins_approach1 << endl;
    cout << "Minimum Number of Coins (Approach 2): " << minCoins_approach2 << endl;

    system("pause");
}