/*
Problem Statement
    	
Bomb Man is trapped inside a maze shaped like a grid. You must help him find the exit as fast as possible. The maze will be given as a String[] where each element corresponds to a row in the grid and each character in an element corresponds to a cell in that row. '#' marks a wall, '.' an empty cell, 'B' the start position of Bomb Man and 'E' the exit. Below is an example of a maze in this format, given as a String[]:

{".....B.",
 ".#####.",
 ".#...#.",
 ".#E#.#.",
 ".###.#.",
 "......."}
In each time unit, Bomb Man can move one cell up, down, left or right. Thus, in the maze above, he can reach the exit in 14 time units by just walking.

To be able to reach the exit quicker, Bomb Man is in possession of a number of bombs, each of which can blow a hole in a wall and thus open up new passages. Instead of moving in any of the four cardinal directions, Bomb Man can (if he has bombs left) blow a hole in a wall located in any of the four neighboring squares. The bomb will go off in the time unit after he has placed the bomb, creating an empty cell that Bomb Man can enter in the time unit after that. That is, if he places a bomb in time unit t, he can enter the cell earliest in time unit t+2. In the maze above, Bomb Man can then reach the exit in 8 time units by first walking left, placing a bomb, waiting for the bomb to explode, and then walking down, down, left, left and down.

Create a class BombMan containing the method shortestPath which takes a String[] maze, containing the maze in the format described above, and an int bombs, the number of bombs in Bomb Man's possession. The method should return an int, the least number of time units required for Bomb Man to reach the exit. If it's not possible for Bomb Man to reach the exit, return -1 (see example 1).

 
Definition
    	
Class:	BombMan
Method:	shortestPath
Parameters:	String[], int
Returns:	int
Method signature:	int shortestPath(String[] maze, int bombs)
(be sure your method is public)
    
 
Constraints
-	maze will contain between 1 and 50 elements, inclusive.
-	Each element in maze will contain between 1 and 50 characters, inclusive.
-	Each element in maze will contain the same number of characters.
-	maze will only contain the characters '#', '.', 'B' and 'E'.
-	Exactly one character in maze will be a 'B'.
-	Exactly one character in maze will be a 'E'.
-	bombs will be between 0 and 100, inclusive.
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

struct Point
{
    Point() : x(0), y(0) { }
    Point(const Point& p) { x = p.x; y = p.y; }
    Point(int tx, int ty) : x(tx), y(ty) {}
    int x, y;

    bool operator==(const Point& p)
    {
        return (x == p.x && y == p.y);
    }
};

struct Node
{
    Node() { }

    Node(Point tp, vector<Point> prevPts, int tmpCost, int bmbLeft) : p(tp), prevPoints(prevPts), cost(tmpCost), bombsLeft(bmbLeft) 
    {
        prevPoints.push_back(tp);
    }
    
    Node(int x, int y, int tmpCost, int bmbLeft) : cost(tmpCost), bombsLeft(bmbLeft)
    {
        p = Point(x, y);
        prevPoints.push_back(p);
    }

    Node(const Node& copy)
    {
        p = copy.p;
        cost = copy.cost;
        bombsLeft = copy.bombsLeft;
        prevPoints = copy.prevPoints;
    }

    bool operator==(const Node& rhs)
    {
        if (p == rhs.p)
            return true;
        return false;
    }
    
    Point p;
    vector<Point> prevPoints;
    int cost;
    int bombsLeft;
};

bool operator<(const Node& lhs, const Node& rhs)
{
    return (lhs.cost > rhs.cost);
}

class BombMan 
{
private:
    int mazeWidth, mazeHeight;
    Point startPt;
    Point endPt;

    vector < vector<bool> > visited_maze;

    void findBombman(const vector<string>& maze)
    {
        bool foundStart = false, foundEnd = false;
        mazeWidth = maze[0].length();
        mazeHeight = maze.size();

        vector < vector<bool> > myMaze(mazeWidth, vector<bool>(mazeHeight, false));
        visited_maze = myMaze;

        for (int i = 0; i < mazeHeight; ++i)
        {
            for (int j = 0; j < mazeWidth; ++j)
            {
                if (maze[i][j] == 'B')
                {
                    startPt.x = j;
                    startPt.y = i;
                    foundStart = true;
                }

                if (maze[i][j] == 'E')
                {
                    endPt.x = j;
                    endPt.y = i;
                    foundEnd = true;
                }

                if (foundStart && foundEnd)
                    return;
            }
        }
    }

    enum direction
    {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    };


    int cost(const vector<string>& maze, const Point& currentPt, direction d, int bombsLeft,
             Point& newPt)
    {
        if (d == UP && (currentPt.y - 1) < 0) return -1;
        if (d == DOWN && (currentPt.y + 1) >= mazeHeight) return -1;
        if (d == LEFT && (currentPt.x - 1) < 0) return -1;
        if (d == RIGHT && (currentPt.x + 1) >= mazeWidth) return -1;

        char val = ' ';

        switch(d)
        {
        case UP: 
            newPt.x = currentPt.x; newPt.y = currentPt.y - 1;
            val = maze[newPt.y][newPt.x];  
            break;

        case DOWN:
            newPt.x = currentPt.x; newPt.y = currentPt.y + 1;
            val = maze[newPt.y][newPt.x]; 
            break;

        case LEFT:
            newPt.x = currentPt.x - 1; newPt.y = currentPt.y;
            val = maze[newPt.y][newPt.x]; 
            break;

        case RIGHT:
            newPt.x = currentPt.x + 1; newPt.y = currentPt.y;
            val = maze[newPt.y][newPt.x]; 
            break;
        }

        if (visited_maze[newPt.x][newPt.y] == true)
            return -1;

        if (val == '.' || val == 'E') return 1;

        if (val == '#' && bombsLeft > 0) 
            return 3;

        return -1;
    }

public:
	int shortestPath(vector <string> maze, int bombs) 
    {
        findBombman(maze);

		priority_queue<Node> pq;

        pq.push(Node(startPt.x, startPt.y, 0, bombs));

        while (!pq.empty())
        {
            // Now find all the possible paths from this point
            Node top = pq.top();
            pq.pop();

            //for (int i = 0; i < top.prevPoints.size(); ++i)
            //    cout << top.prevPoints[i].x << " , " << top.prevPoints[i].y << " --> ";

            //cout << endl;

            visited_maze[top.p.x][top.p.y] = true;

            // Check for termination condition
            if (top.p == endPt)
                return top.cost;

            // Find all the paths we can go from here.
            for (int i = 0; i < 4; ++i)
            {
                Point newPt;
                int current_cost = cost(maze, top.p, (direction)i, top.bombsLeft, newPt);
                
                if (current_cost == -1)
                    continue;

                Node n;
                
                int bombsLeft = top.bombsLeft;

                if (current_cost == 3)
                    bombsLeft -= 1;

                n = Node(newPt, top.prevPoints, top.cost + current_cost, bombsLeft);

                pq.push(n);
            }
        }

        return -1;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, int p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << p1;
	cout << "]" << endl;
	BombMan *obj;
	int answer;
	obj = new BombMan();
	clock_t startTime = clock();
	answer = obj->shortestPath(p0, p1);
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
	
	vector <string> p0;
	int p1;
	int p2;
	
	{
	// ----- test 0 -----
	string t0[] = {".....B.",".#####.",".#...#.",".#E#.#.",".###.#.","......."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 8;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"B.#.#.#...E"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = -1;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}

    {
	// ----- test 1 -----
	string t0[] = {"B.........E"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 10;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}

    
    
	{
	// ----- test 2 -----
	string t0[] = {"..#####","B.#####","..#####","#######","####...","####.E."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4;
	p2 = 17;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {".#.#.#.#B#...#.#...#.#...#.#...#.#...#.#.#.......",".#.#.#.#.#.###.###.#.###.#.#.###.###.#.#.#.###.##",".#.#.#...#.#.#.#.#.#...#.....#.#.#...#...#.#.#...",".#.#.###.#.#.#.#.#.###.#.#####.#.###.###.#.#.###.",".............#.#...#...#.....#.#.#...#.#.#.....#.","##.#######.###.#.#####.#.#####.#.###.#.#.#.#.####",".#.#.....#...#...#.#...#...#.#.#...#...#...#.....",".#######.#.#####.#.#.#.#.###.#.###.#.#####.#.####",".#.#.#.#...#.#.#.#.#.#.......#...#.#...#.#.#.....",".#.#.#.###.#.#.#.#.#####.#####.###.###.#.#.######",".....#...#.#...#...#...#...#...#...#.#.#.........","####.###.#.###.###.#.###.#.#.###.###.#.#.########",".......#.........#.#.#.#.#.#.#.#.........#...#...",".#.###.#########.#.#.#.#.###.#.#####.#.#.#.###.##",".#.#.........#.#.#.#.#.....#.#.#.....#.#.........","############.#.#.#.#.#.#####.#.#.################",".#...........#...#.#.#.#...#.#.#...#.#.#.....#...",".#####.#####.###.#.#.#.#.###.#.#.###.#.#.#####.##",".......#...#.#.#.....#...#...#.#.#.#.#...........","##########.#"
			".#.#####.#.###.###.#.#.#.#.##########",".....#...#.....#.#...#.......#.#...#.......#.....","##.#.###.#.###.#.#.#.#.#####.#.#.###.#######.####","...#...#...#.......#.....#.#...#...#.......#.....","####.#.#.#########.#.###.#.#####.###.#.#######.##",".#...#...#.........#.#.....#.........#.#.#.#.....",".#####.#.#.###.#######.#.###.#.#########.#.#.####",".......#.#.#...#.......#.....#.#.#.......#.#.#.#.","########.#.#.#.#####.#.###.#.###.#.#######.#.#.#.",".........#.#.#.#.....#...#.#.........#.#.........","################.#.#.#.#.#.#.#.#######.#.########",".................#.#.#.#.#.#.#...........#.......","########.#####.#.###.#.#.#####.###.#.#####.###.##",".........#...#.#...#.#.#...#.....#.#.........#...",".#####.#####.#.###.#.###.#.#.#.#.#.#####.#.###.#.",".#.....#.........#.#.#...#.#.#.#.#.#.....#...#.#.","####.#####.###.#.#.#.#.#.#.###.###.#.#.#.#.#####.",".....#.....#.#.#.#.#.#.#.#.#...#...#.#.#.#...#...","####.#.#.###.#.#.###.#.###.#.#.#####.#.#.#.######",".....#.#.#.#...#...#.#..."
			"#.#.#...#...#.#.#.......","##########.#.#.#.#####.###.#.#.###.#.###.#####.##","...#.#...#...#.#.....#.#...#.#...#.#.#.......#...",".#.#.#.#.#.#.#.#.#.#.###.#.#########.###.#.#.#.#.",".#.#...#...#.#.#.#.#...#.#...#.......#...#.#.#.#.","##.###.#.#.###.#.#.#.#.#####.#.#.#.###.#.########",".......#.#...#.#.#.#.#.#.....#.#.#...#.#.........","####.#######.#.#####.#.###.#.#.###.#.#.#.########","E..#.......#.#.....#.#.#.#.#.#.#...#.#.#.........","##.#.#.#.###.###.###.###.#.#.###.#.#.#.#.#######.",".....#.#...#.#.....#.#.....#...#.#.#.#.#.....#..."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	p2 = 76;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
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
