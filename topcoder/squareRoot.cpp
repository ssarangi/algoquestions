#include <vector>
#include <iostream>

using namespace std;

int binarySearch(vector<int>& possibleCandidates, int startSearchIndex, int endSearchIndex, int num)
{
    while (startSearchIndex != endSearchIndex)
    {
        int searchIndex = (startSearchIndex + endSearchIndex) / 2;
        int sq = possibleCandidates[searchIndex] * possibleCandidates[searchIndex]; 
        if (sq < num)
        {
            startSearchIndex = searchIndex + 1;
        }
        else if (sq > num)
        {
            endSearchIndex = searchIndex - 1;  
        }
        else
        {
            startSearchIndex = endSearchIndex = searchIndex;
        }

    }

    if (startSearchIndex * startSearchIndex == num)
        return startSearchIndex;

    return -1;
}

int computeSquareRoot(int num)
{
    vector<int> possibleCandidates;

    int maxVal = 0;
    if (num < 10)
        maxVal = (int)ceil((double)num / 2.0);
    else
        maxVal = (int)ceil((double)num / 4.0);

    // Now generate numbers between that
    for (int i = 0; i <= maxVal; ++i)
        possibleCandidates.push_back(i);

    return binarySearch(possibleCandidates, 0, possibleCandidates.size() - 1, num);
}

int main(void)
{
    int num;
    // Compute the square root
    cout << "Enter number: ";
    cin >> num;
    int sqRoot = computeSquareRoot(num);
    if (sqRoot == -1)
        cout << "\nNo Square Root" << endl;
    else
        cout << "Square Root: " << sqRoot << endl;

    system("pause");
}

