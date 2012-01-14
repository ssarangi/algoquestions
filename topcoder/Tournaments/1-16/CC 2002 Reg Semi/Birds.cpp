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
#include <assert.h>

using namespace std;

typedef long long ll;

ll toInt(string s) {stringstream in(s, ios_base::in); ll result; in >> result; return result;}

vector<string> &split(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) 
{
    vector<string> elems;
    return split(s, delim, elems);
}

struct BirdStruct
{
    int x, y;
    int day, month;
    bool redundant;
};

struct Region
{
    Region(const BirdStruct& bs)
    {
        stops.push_back(bs);
    }

    vector<BirdStruct> stops;
};

BirdStruct getBirdStruct(string param)
{
    vector<string> arr = split(param, ',');
    BirdStruct bs;
    bs.x     = (int)toInt(arr[0]);
    bs.y     = (int)toInt(arr[1]);
    bs.month = (int)toInt(arr[2]);
    bs.day   = (int)toInt(arr[3]);

    return bs;
}

bool operator<(const BirdStruct& b1, const BirdStruct& b2)
{
    if (b1.month > b2.month || (b1.month <= b2.month && b1.day > b2.day))
        return false;

    return true;
}

int getNumDaysInMonth(int month)
{
    switch(month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;

    case 2:
        return 28;
        break;

    default:
        return 30;
        break;
    }
}

int getNumDays(int m1, int d1, int m2, int d2)
{
    if (m2 == m1)
        return (d2 - d1 + 1);

    int current_month = m1;
    int num_days = 0;
    int starting_date = d1;
    while ((m2 - current_month) >= 1)
    {
        int numDaysInMonth = getNumDaysInMonth(current_month);
        num_days += numDaysInMonth - starting_date;
        starting_date = 0;
        current_month++;
    }

    if (m2 == 12 && d2 == 31)
        num_days += d2 + 1;
    else
        num_days += d2 - 1 + 1; // 1 is for the starting date. -1 is because we can't include the ending date.

    return num_days;
}

double getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


class Birds 
{
    vector<BirdStruct> birds;

    int getNumberOfDays(int index)
    {
        if (index == birds.size() - 1)
            return getNumDays(birds[index].month, birds[index].day, 12, 31);
        else
            return getNumDays(birds[index].month, birds[index].day, birds[index+1].month, birds[index+1].day);
    }

    bool isRegionApart(const Region& reg1, const Region& reg2)
    {
        for (int i = 0; i < reg1.stops.size(); ++i)
        {
            for (int j = 0; j < reg2.stops.size(); ++j)
            {
                if (getDistance(reg1.stops[i].x, reg1.stops[i].y, reg2.stops[j].x, reg2.stops[j].y) < 1000)
                    return false;
            }
        }

        return true;
    }


public:
    int isMigratory(vector <string> param0) 
    {
        int current_index = 0;
        for (unsigned int i = 0; i < param0.size(); i++)
        {
            // Remove all duplicate entries.
            BirdStruct bs = getBirdStruct(param0[i]);

            if (birds.empty())
                birds.push_back(bs);

            if (bs.x == birds[current_index].x && bs.y == birds[current_index].y)
                continue;

            birds.push_back(bs);
            current_index++;
        }

        sort(birds.begin(), birds.end());

        // group stops into regions, if two location are less than 1000 miles away from each other
        // according to the question, it is in the same region
        for (int i = 1; i < birds.size(); ++i) {
            if (getDistance(birds[i-1].x, birds[i-1].y, birds[i].x, birds[i].y) < 1000) {
                // mark redundant stops
                birds[i].redundant = true;
            }
        }        

        vector<Region> regions;
        for (int i = 0; i < birds.size(); i++)
        {
            if (birds[i].redundant == false)
                regions.push_back(birds[i]);
            else if (regions.back().stops.back().x != birds[i].x && regions.back().stops.back().y != birds[i].y)
                regions.back().stops.push_back(birds[i]);
        }

        // Calculate Durations
        int numDays = 0;
        vector<int> durations;
        for (int i = 1; i < regions.size(); ++i)
        {
            int dur = getNumDays(regions[i-1].stops[0].month, regions[i-1].stops[0].day, regions[i].stops[0].month, regions[i].stops[0].day);
            durations.push_back(dur);
            numDays += dur;
        }

        durations.push_back(365 - numDays);

        // Check duration, we need to stay in 2 places for more than 90 days
        vector<int> longStays;

        for (int i = 0; i < durations.size(); ++i) 
        {
            if (durations[i] >= 90) 
                longStays.push_back(i);
        }
        
        if (longStays.size() < 2)
            return 0;

        // calcuate distance between longStays
        for (int i = 0; i < longStays.size(); ++i) 
        {
            for (int j = i+1; j < longStays.size(); ++j) 
            {
                if (isRegionApart(regions[i], regions[j]))
                    return 1;
            }
        }

        return 0;
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
    Birds *obj;
    int answer;
    obj = new Birds();
    clock_t startTime = clock();
    answer = obj->isMigratory(p0);
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
    
    
    string results1[] = {"0,0,1,1", "1,1,3,1", "1000,1000,4,1"};
    p0.clear();
    p0.assign(results1, results1 + 3);

    Birds b;
    int result = b.isMigratory(p0);

    if (all_right) {
        cout << "You're a stud (at least on the example cases)!" << endl;
    } else {
        cout << "Some of the test cases had errors." << endl;
    }
    return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
