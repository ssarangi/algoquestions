/*
Problem Statement
    	
Disk Scheduling is an important component of an operating system. The disk (or hard-drive) is composed of a number of cylinders. Each cylinder contains 
circular tracks, which in turn are divided into sectors. To read a particular sector the operating system must determine the cylinder and track it belongs to. 
It then rotates the cylinder so that the disk head is positioned at the desired sector. If the file being used is located on numerous sectors, scattered across 
the track, the disk scheduler must read all those sectors in such a way that minimizes total head movement.

In practice it is impossible to implement an optimal disk scheduling algorithm, because requests to read sectors arrive one after another, instead of being known 
from the start. However, in our problem the order that the sectors are read can be changed to suit the fastest retrieval. The results of a theoretical optimal algorithm 
are useful when comparing the effectiveness of various real-life scheduling algorithms.

For the purpose of this problem assume that a track has 100 sectors numbered from 1 to 100 inclusive. The cylinder can be rotated either clockwise or counter-clockwise. 
The cylinder is circular meaning that sector 1 is adjacent to sector 100. Given the start location of the head determine the minimal head movement required to read all 
the int[] sectors.

 
Definition
    	
Class:	DiskScheduler
Method:	optimize
Parameters:	int, int[]
Returns:	int
Method signature:	int optimize(int start, int[] sectors)
(be sure your method is public)
    
 
Constraints
-	start will be between 1 and 100 inclusive.
-	sectors will contain between 1 and 50 elements inclusive.
-	each element in sectors will be between 1 and 100 inclusive.
-	sectors will not have any repeated elements.
-	start will never be an element of sectors.
 
Examples
0)	
    	
5
{6,8,65,71}
Returns: 46
The path 5->6->8->71->65 gives us the least head movement. In other words, rotate forward from 5 to 8, moving the head 3 sectors. Then rotate from 8 backwards to 71 for a 
total of (8-1) + (100-71) + 1 = 37. Finally rotate from 71 to 65, for a total of 3 + 37 + 16 = 46.
1)	
    	
5
{55,65,71}
Returns: 50
If we do 5->55->65->71 then we require 66 head movements. However if we go in the opposite direction 5->71->65->55 we only require 50 head movements, which is more efficient. 
Note that going from 5 to 71 requires only 5 + 29 = 34 head movements.
2)	
    	
20
{1,21,99}
Returns: 23
If we go 20->1->99->21 that will take 99 head movements. If we go 20->21->99->1 that will take 81 head movements. Finally, if we go 20->21->1->99 that will only take 23 head 
movements.
3)	
    	
99
{55,56,61,70,76,78,80,83,84,90,1,4,6,26,27,33,38,46,47,49}
Returns: 87
The sorted array is {1,4,6,26,27,33,38,46,47,49,55,56,61,70,76,78,80,83,84,90}. The most efficient way is to go right until we reach 6 and then go in the reverse direction until we reach 26.
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, 
Inc. is strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.

This problem was used for: 
       Single Round Match 194 Round 1 - Division II, Level Three
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

using namespace std;

typedef long long ll;

string toString(ll n) {stringstream out(ios_base::out); out << n; return out.str();}

string toString(int n) {return toString((ll)(n));}


struct Node
{
    int sector;
    int cost;
    int pathLength;
    string currentP;

    Node(int s, int c, int p, string path, string cp) : sector(s), cost(c), pathLength(p)
    {  
        currentP = path + "," + cp;
    }

    Node() {}
    Node(const Node& n) { sector = n.sector; cost = n.cost; pathLength = n.pathLength; currentP = n.currentP; }
};

bool operator<(const Node& n1, const Node& n2)
{
    if (n1.cost > n2.cost)
        return true;

    return false;
}


class DiskSchedulerOld
{
    int getCost(Node startSector, int end)
    {
        string endS = toString(end);
        if (startSector.currentP.find(endS) != string::npos)
            return -1;

        int start = startSector.sector;

        if (start > end)
            swap(start, end);

        int cost = min((end - start), (start - 1) + (100 - end) + 1);
        return cost;
    }

public:
	int optimizeDijkstra(int start, vector <int> sectors) 
    {
        priority_queue<Node> pq;

        vector<int> currentPath;

        pq.push(Node(start, 0, 0, "", ""));

        while (!pq.empty())
        {
            Node top = pq.top();
            pq.pop();

            if (top.pathLength == sectors.size())
                return top.cost;

            for (unsigned int i = 0; i < sectors.size(); ++i)
            {
                if (sectors[i] == top.sector)
                    continue;

                int cost = getCost(top, sectors[i]);
                if (cost != -1)
                    pq.push(Node(sectors[i], top.cost + cost, top.pathLength + 1, top.currentP, toString(top.sector)));
            }
        }

        return -1;
	}
};

class DiskScheduler
{
    vector<int> d;

    int sweep(int pos, int incr, int num)
    {
        int count = 0;

        while (num)
        {
            if (d[pos] == 1)
                --num;

            pos += incr;
            ++count;
        }

        return count;
    }


public:
	int optimize(int start, vector <int> sectors) 
    {
        d.resize(200, 0);
        for (int i = 0; i < sectors.size(); i++)
            d[sectors[i]] = d[sectors[i] + 100] = 1;

        // Either Left or right
        int res = min(sweep(start + 100, 1, sectors.size()), sweep(start + 100, -1, sectors.size()));

        for (int i = 0; i < 100; ++i)
        {
            int count = 0;
            for (int j = 0; j <= i; ++j)
            {
                if (d[start + 100 + j] == 1)
                    ++count;
            }

            res = min(res, 2 * i + sweep(start + 100, -1, sectors.size() - count));

            for (int j = 0; j <= i; ++j)
            {
                if (d[start + 100 - j] == 1)
                    ++count;
            }

            res = min(res, 2 * i + sweep(start + 100, 1, sectors.size() - count));
        }

        return res - 1;
    }
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}";
	cout << "]" << endl;
	DiskScheduler *obj;
	int answer;
	obj = new DiskScheduler();
	clock_t startTime = clock();
	answer = obj->optimize(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
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
	vector <int> p1;
	int p2;
	
	{
	// ----- test 0 -----
	p0 = 5;
	int t1[] = {6,8,65,71};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 46;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	//{
	//// ----- test 1 -----
	//p0 = 5;
	//int t1[] = {55,65,71};
	//		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	//p2 = 50;
	//all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	//// ------------------
	//}
	
	//{
	//// ----- test 2 -----
	//p0 = 20;
	//int t1[] = {1,21,99};
	//		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	//p2 = 23;
	//all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	//// ------------------
	//}

	//{
	//// ----- test 3 -----
	//p0 = 20;
	//int t1[] = {55,56,61,70,76,78,80,83,84};
	//		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	//p2 = 87;
	//all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	//// ------------------
	//}


	//{
	//// ----- test 3 -----
	//p0 = 99;
	//int t1[] = {55,56,61,70,76,78,80,83,84,90,1,4,6,26,27,33,38,46,47,49};
	//		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	//p2 = 87;
	//all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	//// ------------------
	//}
	
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
