// FInd the maximum sum of a sub-sequence from an positive integer array where 
// any two numbers of sub-sequence are not adjacent to each other in the original 
// sequence. E.g 1 2 3 4 5 6 --> 2 4 6

#include <iostream>
#include <algorithm>

using namespace std;

int find_max_subsequence(vector<int> numList, int startPt)
{
    int maxsofar = 0;
    int maxendinghere = 0;

    for (int i = startPt; i < numList.size(); i+=2)
    {
        maxendinghere = max(maxendinghere + numList[i], 0);
        maxsofar = max(maxsofar, maxendinghere);
    }

    return maxsofar;
}

int main(void)
{
    int length;
    vector<int> numList;

    cout << "Max Length: ";
    cin >> length;

    for (int i = 0; i < length; ++i)
    {
        int val;
        cin >> val;
        numList.push_back(val);
    }
    
    int maxsofar = 0;
    for (int i = 0; i < numList.size(); ++i)
    {
        maxsofar = max(maxsofar, find_max_subsequence(numList, i));
    }

    cout << "Max Subsequence: " << maxsofar << endl;
    return 0;
}
