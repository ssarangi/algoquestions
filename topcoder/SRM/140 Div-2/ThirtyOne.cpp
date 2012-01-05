/*
Problem Statement
    	
Thirty One is a card game for 2 or more players. The game can be played with one or more decks of standard cards. The aim of the game is to 
try and make the value of your hand as close to 31 points as possible without going over 31 points. A hand consists of exactly 3 cards.

Each number card (2, 3, ... 9, 10) is worth the value written on the card; Jack (J), Queen (Q) and King (K) are all worth 10; while an Ace (A) 
is worth either 1 or 11 depending on which will give a greater total without going over 31 points. There is one exception however; if a hand consists 
of 3 identical cards then the value of that hand automatically becomes 30.5 points.

Each element in hands will contain exactly three cards, where cards are separated by exactly one space. For example "A 10 K" is a hand consisting of Ace, 
10 and King. The value of this hand is 11 + 10 + 10 = 31. Note that we chose Ace to be 11 and not 1 since that gives us a greater total without exceeding 31.

Given a String[] of players' hands return the index of the winning player, where element i (0-indexed) in hands belongs to player i. If two or more players 
are tied for the lead then return the player with the lower index.

 
Definition
    	
Class:	ThirtyOne
Method:	findWinner
Parameters:	String[]
Returns:	int
Method signature:	int findWinner(String[] hands)
(be sure your method is public)
    
 
Constraints
-	hands will contain between 2 and 50 elements inclusive.
-	each element in hands will have exactly three cards, where cards are separated by exactly one space add that there are no leading/trailing spaces.
-	cards in hands will be 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.
 
Examples
0)	
    	
{"10 A A", "K 2 3"}
Returns: 0
The value of the first hand is 10 + 11 + 1 = 22. Notice that we chose the last Ace to be 1, otherwise our total would have been over 31. The value of the 
second hand is 10 + 2 + 3 = 15. The first hand is closer to 31 so it wins.
1)	
    	
{"2 3 4", "10 6 8", "A K 3"}
Returns: 1
The value of the first hand is 2 + 3 + 4 = 9. The value of the second hand is 10 + 6 + 8 = 24. The value of the third hand is 11 + 10 + 3 = 24. However the 
second hand wins since it comes earlier than the third hand.
2)	
    	
{"J 5 2","2 7 5","10 J 2","J 6 2","J Q K"}
Returns: 4
3)	
    	
{"Q K K", "10 J Q", "A 8 A", "2 2 2"}
Returns: 3
The last hand has three identical cards so its value is 30.5
4)	
    	
{"Q 6 6","7 8 3","3 7 2","K Q 6","Q 6 3","5 3 8","10 J Q","4 8 4","Q 2 5","8 A 8",
"9 10 10","2 K 5","10 4 5","Q 4 Q","3 J 2","7 4 4","3 9 7","A 4 4","Q 7 7","10 9 A",
"J 3 5","5 8 9","Q Q 7"}
Returns: 6
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior 
written consent of TopCoder, Inc. is strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.

This problem was used for: 
       Single Round Match 194 Round 1 - Division I, Level One 
       Single Round Match 194 Round 1 - Division II, Level Two
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
ll toInt(string s) {stringstream in(s, ios_base::in); ll result; in >> result; return result;}

inline vector<string> tokenize(string s)
{
    vector<string> tokens;
    istringstream iss(s);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(), 
         back_inserter<vector<string> >(tokens));

    return tokens;
}



class ThirtyOne 
{
    bool isSame(vector<string>& tokens)
    {
        bool isNotSame = false;
        string firstToken = tokens[0];

        for (int i = 1; i < tokens.size(); i++)
        {
            if (firstToken != tokens[i])
            {
                isNotSame = true;
            }
        }

        return (!isNotSame);
    }

    double computeScore(string s, const double currentScore)
    {
        // Ignore the A. We will find its value later
        if (s == "A")
        {
            if (currentScore + 11 <= 31)
                return 11.0;
            else
                return 1.0;
        }

        if (s == "J" || s == "Q" || s == "K")
            return 10.0;

        double score = (double)toInt(s);
        return score;
    }


    double getTotalScore(string s)
    {
        double score = 0;
        vector<string> tokens = tokenize(s);

        if (isSame(tokens))
            return 30.5;

        for (int i = 0; i < tokens.size(); i++)
                score += computeScore(tokens[i], score);

        return score;
    }


public:
	int findWinner(vector <string> hands) 
    {
        vector<double> scores(hands.size(), 0);

        for (int i = 0; i < hands.size(); ++i)
        {
            scores[i] = getTotalScore(hands[i]);
        }
        
        // Now find the hand with the lowest index.
        auto iter = max_element(scores.begin(), scores.end());
        int index = iter - scores.begin();
        double maxVal = *(max_element(scores.begin(), scores.end()));

        return index;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	ThirtyOne *obj;
	int answer;
	obj = new ThirtyOne();
	clock_t startTime = clock();
	answer = obj->findWinner(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
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
	
	vector <string> p0;
	int p1;
	
	{
	// ----- test 0 -----
	string t0[] = {"10 A A","K 2 3"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 0;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"2 3 4","10 6 8","A K 3"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"J 5 2","2 7 5","10 J 2","J 6 2","J Q K"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"Q K K","10 J Q","A 8 A","2 2 2"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"Q 6 6","7 8 3","3 7 2","K Q 6","Q 6 3","5 3 8","10 J Q","4 8 4","Q 2 5","8 A 8","9 10 10","2 K 5","10 4 5","Q 4 Q","3 J 2","7 4 4","3 9 7","A 4 4","Q 7 7","10 9 A","J 3 5","5 8 9","Q Q 7"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 6;
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
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
