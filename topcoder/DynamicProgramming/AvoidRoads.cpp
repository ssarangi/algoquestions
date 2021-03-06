/*
In the city, roads are arranged in a grid pattern. Each point on the grid represents a corner where two blocks meet. The points are 
connected by line segments which represent the various street blocks. Using the cartesian coordinate system, we can assign a pair of 
integers to each corner as shown below. 

You are standing at the corner with coordinates 0,0. Your destination is at corner width,height. You will return the number of distinct 
paths that lead to your destination. Each path must use exactly width+height blocks. In addition, the city has declared certain street blocks 
untraversable. These blocks may not be a part of any path. You will be given a String[] bad describing which blocks are bad. If (quotes for clarity) 
"a b c d" is an element of bad, it means the block from corner a,b to corner c,d is untraversable. For example, let's say
width  = 6
length = 6
bad = {"0 0 0 1","6 6 5 6"}
The picture below shows the grid, with untraversable blocks darkened in black. A sample path has been highlighted in red.
 
Definition
    	
Class:	AvoidRoads
Method:	numWays
Parameters:	int, int, String[]
Returns:	long
Method signature:	long numWays(int width, int height, String[] bad)
(be sure your method is public)
    
 
Constraints
-	width will be between 1 and 100 inclusive.
-	height will be between 1 and 100 inclusive.
-	bad will contain between 0 and 50 elements inclusive.
-	Each element of bad will contain between 7 and 14 characters inclusive.
-	Each element of the bad will be in the format "a b c d" where,
a,b,c,d are integers with no extra leading zeros,
a and c are between 0 and width inclusive,
b and d are between 0 and height inclusive,
and a,b is one block away from c,d.
-	The return value will be between 0 and 2^63-1 inclusive.
 
Examples
0)	
    	
6
6
{"0 0 0 1","6 6 5 6"}
Returns: 252
Example from above.
1)	
    	
1
1
{}
Returns: 2
Four blocks aranged in a square. Only 2 paths allowed.
2)	
    	
35
31
{}
Returns: 6406484391866534976
Big number.
3)	
    	
2
2
{"0 0 1 0", "1 2 2 2", "1 1 2 1"}
Returns: 0
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.




This problem was used for: 
       2003 TCO Semifinal Round 4 - Division I, Level One
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long ll;
       
string toString(ll n) {stringstream out(ios_base::out); out << n; return out.str();}

string toString(int n) {return toString((ll)(n));}

struct Coord
{
    int x, y;

    Coord() : x(0), y(0) { }

    Coord(int a, int b) : x(a), y(b) { }

    string getStr() 
    { 
        return string(toString(x) + " " + toString(y)); 
    }

    bool operator==(const Coord& rhs)
    {
        return (x == rhs.x && y == rhs.y);
    }
};


class AvoidRoads 
{
    unordered_map<string, bool> badMap;
    Coord startPoint;
    Coord endPoint;
    int TotalWidth, TotalHeight;

    void initializeMap(vector<string>& bad)
    {
        for (int i = 0; i < bad.size(); i++)
        {
            badMap[bad[i]] = false;
        }
    }

    bool isPossible(Coord start, Coord end)
    {
        string hash1 = start.getStr() + " " + end.getStr();
        string hash2 = end.getStr() + " " + start.getStr();
        if (badMap.count(hash1) == 0 && badMap.count(hash2) == 0)
            return true;

        return false;
    }

    vector<Coord> possiblePaths(Coord p, Coord prevPoint)
    {
        Coord right = Coord(p.x + 1, p.y);
        Coord up    = Coord(p.x, p.y + 1);

        vector<Coord> paths;

        if (right.x <= TotalWidth && !(right == prevPoint) && isPossible(p, right))
            paths.push_back(right);

        if (up.y <= TotalHeight && !(up == prevPoint) && isPossible(p, up))
            paths.push_back(up);
        
        return paths;
    }

    long long findPaths(Coord currentPt, Coord prevPoint, int pathLength)
    {
        long long totalNum = 0;

        if (currentPt == endPoint)
        {
            if (pathLength == (TotalWidth + TotalHeight))
                return 1;
            else
                return 0;
        }

        if (pathLength > (TotalWidth + TotalHeight))
            return 0;

        // Still not the end.
        vector<Coord> nextPaths = possiblePaths(currentPt, prevPoint);
        if (nextPaths.size() == 0)
            return 0;

        for (int i = 0; i < nextPaths.size(); i++)
        {
            totalNum += findPaths(nextPaths[i], currentPt, pathLength + 1);
        }

        return totalNum;
    }

public:

    AvoidRoads() { }

	long long numWays(int width, int height, vector <string> bad) 
    {
        TotalWidth = width; TotalHeight = height;

	    startPoint = Coord(0, 0);
        endPoint = Coord(width, height);

        initializeMap(bad);

        // Now find path by recursion.
        long long totalPaths = findPaths(startPoint, startPoint, 0);

        return totalPaths;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, vector <string> p2, bool hasAnswer, long long p3) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p2[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	AvoidRoads *obj;
	long long answer;
	obj = new AvoidRoads();
	clock_t startTime = clock();
	answer = obj->numWays(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p3;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	int p1;
	vector <string> p2;
	long long p3;
	
	{
	// ----- test 0 -----
	p0 = 2;
	p1 = 2;
    string t2[] = {"1 1 2 1"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 4;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 0 -----
	p0 = 6;
	p1 = 6;
	string t2[] = {"0 0 0 1","6 6 5 6"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 252ll;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	p0 = 1;
	p1 = 1;
	p2.clear() /*{}*/;
	p3 = 2ll;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 35;
	p1 = 31;
	p2.clear() /*{}*/;
	p3 = 6406484391866534976ll;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 2;
	p1 = 2;
	string t2[] = {"0 0 1 0","1 2 2 2","1 1 2 1"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0ll;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
    system("pause");
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
