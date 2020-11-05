//
// Udacity.com - C++ Nanodegree Program
// Course 2 - Foundations
// main.cpp
//
//  Created by Phyllip Hall on 11/4/20.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

enum class State {kEmpty, kObstacle, kClosed, kPath};

// CellString converts each state to an appropriate string
string CellString(State val){
    switch (val) {
        case State::kObstacle : return "⛰️   ";
        case State::kPath : return "🚗   ";
        default : return "0   ";
    }
}

// TODO: Add the ReadBoardFile function here.
vector<State> ParseLine(string line){
    vector<State> row_out;
    int n;
    char c;
    
    istringstream my_stream(line);
    
    while (my_stream >> n >> c && c == ',') {
        if (n == 0) {
            row_out.push_back(State::kEmpty);
        } else {
            row_out.push_back(State::kObstacle);
        }
    }
    return row_out;
}

vector<vector<State>> ReadBoardFile(string file) {
    vector<vector<State>> board;
    ifstream my_file;
    my_file.open(file);
    if (my_file) {
      string line;
      while (getline(my_file, line)) {
          board.push_back(ParseLine(line));
      }
    }
  return board;
  }

// PrintBoard not used in this exercise
void PrintBoard(const vector<vector<State>> grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      cout << CellString(grid[i][j]);
    }
    cout << "\n";
  }
}

int GetFValue(vector<int> node) {
    int g_value = node[2];  // distance back to start
    int heuristic = node[3];  // <= distance to goal
    return g_value + heuristic;
}

bool Compare(vector<int> node1, vector<int> node2) {
    return GetFValue(node1) > GetFValue(node2);
}

/**  SUPPLIED BY COURSE
 * Sort the two-dimensional vector of ints in descending order.
 */
#include <algorithm>
using std::sort;
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

int Heuristic (int x1, int y1, int x2, int y2) {
    // calculate the Manhattan distance within a grid
    return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen (int x, int y, int g, int h, vector<vector<int>> &nodes, vector<vector<State>> &grid) {
    // add node to nodes list
    vector<int> new_node = {x, y, g, h};
    nodes.push_back(new_node);
    
    // initialize gride value
    grid[x][y] = State::kClosed;
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
    // check input - x value
    if (grid.size() < x) {
        cout << "CheckValidCell: Invalid input value x: " << x << "/n";
        return false;
    }
    
    // check input - y value
    if (grid[x].size() < y) {
        cout << "CheckValidCell: Invalid input value y: " << y << "/n";
        return false;
    }
    
    // return true if grid position x, y is empty
    return (grid[x][y] == State::kEmpty);
}

vector<vector<State>> Search (vector<vector<State>> grid, int start[2], int goal[2]) {
    // return the grid with a path from the start to the goal
    vector<vector<State>> solution;
    
    // create vector of open nodes
    vector<vector<int>> open_nodes {};
    
    // create start node
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, start[1], goal[0], goal[1]);
    AddToOpen(x, y, g, h, open_nodes, grid);
    
    while (open_nodes.size() > 0) {
        // sort open nodes
        CellSort(&open_nodes);
        
        // pop current node
        vector<int> current_node = open_nodes.back();
        open_nodes.pop_back();
        
        // update grid position of popped node
        x = current_node[0];
        y = current_node[1];
        grid[x][y] = State::kPath;
        
        // check: reached goal
        if (goal[0] == x && goal[1] == y) {
            return grid;
        }
            
        // expand search to current nodes neighbors
        
    }
    
    // TODO - stub
    cout << "No path found!" << "\n";
    return solution;
}

int main() {
    // retrieve board from file
    vector<vector<State>> grid = ReadBoardFile("1.board");
    vector<vector<State>> solution;
    
    // set board start and end
    int start[2]={0, 0};
    int goal[2]={4, 5};
    
    // search
    solution = Search(grid, start, goal);
    
    // show results
    PrintBoard(solution);
}
