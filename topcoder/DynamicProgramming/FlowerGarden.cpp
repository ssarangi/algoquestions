/*
Problem Statement
    	
You are planting a flower garden with bulbs to give you joyous flowers throughout the year. However, you wish to plant the flowers 
such that they do not block other flowers while they are visible.

You will be given a int[] height, a int[] bloom, and a int[] wilt. Each type of flower is represented by the element at the same index 
of height, bloom, and wilt. height represents how high each type of flower grows, bloom represents the morning that each type of flower 
springs from the ground, and wilt represents the evening that each type of flower shrivels up and dies. Each element in bloom and wilt 
will be a number between 1 and 365 inclusive, and wilt[i] will always be greater than bloom[i]. You must plant all of the flowers of the 
same type in a single row for appearance, and you also want to have the tallest flowers as far forward as possible. However, if a flower 
type is taller than another type, and both types can be out of the ground at the same time, the shorter flower must be planted in front of 
the taller flower to prevent blocking. A flower blooms in the morning, and wilts in the evening, so even if one flower is blooming on the same 
day another flower is wilting, one can block the other.

You should return a int[] which contains the elements of height in the order you should plant your flowers to acheive the above goals. The front 
of the garden is represented by the first element in your return value, and is where you view the garden from. The elements of height will all be 
unique, so there will always be a well-defined ordering.

 
Definition
    	
Class:	FlowerGarden
Method:	getOrdering
Parameters:	int[], int[], int[]
Returns:	int[]
Method signature:	int[] getOrdering(int[] height, int[] bloom, int[] wilt)
(be sure your method is public)
    
 
Constraints
-	height will have between 2 and 50 elements, inclusive.
-	bloom will have the same number of elements as height
-	wilt will have the same number of elements as height
-	height will have no repeated elements.
-	Each element of height will be between 1 and 1000, inclusive.
-	Each element of bloom will be between 1 and 365, inclusive.
-	Each element of wilt will be between 1 and 365, inclusive.
-	For each element i of bloom and wilt, wilt[i] will be greater than bloom[i].
 
Examples
0)	
    	
{5,4,3,2,1}
{1,1,1,1,1}
{365,365,365,365,365}
Returns: { 1,  2,  3,  4,  5 }
These flowers all bloom on January 1st and wilt on December 31st. Since they all may block each other, you must order them from shortest 
to tallest.
1)	
    	
{5,4,3,2,1}
{1,5,10,15,20}
{4,9,14,19,24}
Returns: { 5,  4,  3,  2,  1 }
The same set of flowers now bloom all at separate times. Since they will never block each other, you can order them from tallest to shortest 
to get the tallest ones as far forward as possible.
2)	
    	
{5,4,3,2,1}
{1,5,10,15,20}
{5,10,15,20,25}
Returns: { 1,  2,  3,  4,  5 }
Although each flower only blocks at most one other, they all must be ordered from shortest to tallest to prevent any blocking from occurring.
3)	
    	
{5,4,3,2,1}
{1,5,10,15,20}
{5,10,14,20,25}
Returns: { 3,  4,  5,  1,  2 }
The difference here is that the third type of flower wilts one day earlier than the blooming of the fourth flower. Therefore, we can put the 
flowers of height 3 first, then the flowers of height 4, then height 5, and finally the flowers of height 1 and 2. Note that we could have also 
ordered them with height 1 first, but this does not result in the maximum possible height being first in the garden.
4)	
    	
{1,2,3,4,5,6}
{1,3,1,3,1,3}
{2,4,2,4,2,4}
Returns: { 2,  4,  6,  1,  3,  5 }
5)	
    	
{3,2,5,4}
{1,2,11,10}
{4,3,12,13}
Returns: { 4,  5,  2,  3 }
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction 
of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.




This problem was used for: 
       2004 TCCC Online Round 1 - Division I, Level Two
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class FlowerGarden
{
    bool isPlantingPossible(int height1, int height2, int bloom1, int wilt1, int bloom2, int wilt2)
    {
        bool planting = true;

        if (height1 > height2)
        { 
            // Case where -------------------  (1) 
            //               -----------       (2)

            // Case where    -----------       (1) 
            //            -------------------  (2)

            // Case where ----------           (1)
            //                  -------------  (2)

            // Case where       -------------  (1)
            //            ----------

            // Whenever there is an intersection.
            if (!((bloom1 < bloom2 && wilt1 < bloom2) || (bloom1 > wilt2 && wilt1 > wilt2)))
                planting = false;
        }

        return planting;
    }

    void display_list(list<int> val)
    {
        auto iter = val.begin();
        for (unsigned int i = 0; i < val.size(); ++i, ++iter)
            cout << (*iter) << " ";
        cout << endl;
    }

    void display_table(vector < vector<bool> > table)
    {
        for (int i = 1; i < 6; ++i)
        {
            for (int j = 1; j < 6; ++j)
            {
                cout << table[i][j] << " ";
            }

            cout << endl;
        }
    }


public:
    list<int> getOrdering(vector<int> height, vector<int> bloom, vector<int> wilt)
    {
        // Initialize all the paths as not accessible. This table stores whether each
        // element can be planted to the right of a larger tree or not.
        // Since max height = 1000
        vector< vector<bool> > table(1001, vector<bool>(1001, false));

        list<int> ordering;

        // Create the table
        for (unsigned int i = 0; i < height.size(); ++i)
        {
            int height1 = height[i];
            int bloom1  = bloom[i];
            int wilt1   = wilt[i];

            for (unsigned int j = 0; j < height.size(); ++j)
            {
                if (i == j)
                    continue;

                // Populate the table
                int height2 = height[j];
                int bloom2  = bloom[j];
                int wilt2   = wilt[j];

                table[height1][height2] = isPlantingPossible(height1, height2, bloom1, wilt1, bloom2, wilt2);
            }
        }

        // Add the max height first. We are then going to reorder this.
        std::sort(height.begin(), height.end());

        ordering.push_back(height[height.size() - 1]);

        // Now add 0's so that we can move the iterator around.
        // ordering.push_front(0);

        for (int i = height.size() - 2; i >= 0; --i)
        {
            // Start at the beginning and then find where to insert
            auto currentIter = ordering.begin(); 

            int currentHeight = height[i];

            bool isPossibleToPlantToLeft;

            do
            {
                // int alreadyAddedHeight = height[alreadyAddedHeightsIndex];
                int alreadyAddedHeight = *currentIter;

                // Now comes the case where the lower elements will try to take over
                // the beginning of the list. In this case check if the higher height 
                // can come before the lower height and if so then give preference to 
                // the higher height.
                if (alreadyAddedHeight > currentHeight)
                    isPossibleToPlantToLeft = table[currentHeight][alreadyAddedHeight] & (!table[alreadyAddedHeight][currentHeight]);
                else
                    isPossibleToPlantToLeft = table[currentHeight][alreadyAddedHeight];

                if (!isPossibleToPlantToLeft)
                    ++currentIter;
            } 
            while (isPossibleToPlantToLeft == false && currentIter != ordering.end());
    
            ordering.insert(currentIter, currentHeight);
            
            display_list(ordering);
        }

        return ordering;
    }
};

int main(void)
{
    int aheight[] = {5,4,3,2,1};
    int abloom[]  = {1, 1, 1, 1, 1};
    int awilt[]   = {365, 365, 365, 365, 365};

    //int aheight[] = {5,4,3,2,1};
    //int abloom[]  = {1, 5, 10, 15, 20};
    //int awilt[]   = {4, 9, 14, 19, 24};

    //int aheight[] = {5,4,3,2,1};
    //int abloom[]  = {1, 5, 10, 15, 20};
    //int awilt[]   = {5, 10, 15, 20, 25};

    //int aheight[] = {5,4,3,2,1};
    //int abloom[]  = {1, 5, 10, 15, 20};
    //int awilt[]   = {5, 10, 14, 20, 25};

    //int aheight[] = {1,2,3,4,5,6};
    //int abloom[]  = {1, 3, 1, 3, 1, 3};
    //int awilt[]   = {2, 4, 2, 4, 2, 4};


    //int aheight[] = {3,2,5,4};
    //int abloom[]  = {1, 2, 11, 10};
    //int awilt[]   = {4, 3, 12, 13};

    const int data_size = 5;

    vector<int> height(data_size);
    std::copy(aheight, aheight + data_size, height.begin());

    vector<int> bloom(data_size);
    std::copy(abloom, abloom + data_size, bloom.begin());

    vector<int> wilt(data_size);
    std::copy(awilt, awilt + data_size, wilt.begin());

    FlowerGarden fw;
    list<int> ordering = fw.getOrdering(height, bloom, wilt);
    auto iter = ordering.begin();

    for (unsigned int i = 0; i < ordering.size(); ++i)
    {
        cout << *iter << " ";
        ++iter;
    }

    cout << endl;

    system("pause");
    return 0;
}

