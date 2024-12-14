#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

const int maxNum = 9;
//add a number to the unsolved puzzle, by iterating through available numbers to find a valid number and placing in the puzzle
bool addToPuzzle(vector<vector<int>> &puzzle, int i, int k) {
    int start;
    int startRow;
    int startCol;
    bool foundNum = false;
    start = puzzle[i][k] +1;
    int countNum = 0;
    vector<int> row(maxNum);
    row = puzzle[i];
    vector<int> col(maxNum);
    for(int p = 0; p < maxNum; p++) {
       col[p] = puzzle[p][k];
    }
    //locate the 3x3 grid location
    if(i < 3) {
        startRow = 0;
    } else if(i < 6) {
        startRow = 3;
    } else {
        startRow = 6;
    }
    if(k < 3) {
        startCol = 0;
    } else if(k < 6) {
        startCol = 3;
    } else {
        startCol = 6;
    }

    
   for(int j = start; j <= maxNum; j++) {
    // check for occurence in 3x3 grid
    for(int r = startRow; r< startRow + 3; r++) {
        for(int c = startCol; c < startCol + 3; c++) {
            if(j == puzzle[r][c]) {
                countNum++;
            }
        }
    }
    //check for occurence in the row and column
    countNum = countNum + count(row.begin(), row.end(), j) + count(col.begin(), col.end(), j);
    if (countNum == 0) {
        foundNum = true;
        puzzle[i][k] = j;
        break;
    }
    countNum = 0;
   }
    


   return foundNum;
}
//uses "filled" stack to find the cell of previosly placed number and reiterates through alternatives
//if not found it will recursevily call previous cell
void backtrack(vector<vector<int>> &puzzle, stack<pair<int, int>> &unsolved, stack<pair<int,int>> &filled) {
    if (!filled.empty()) {
    if (addToPuzzle(puzzle, filled.top().first, filled.top().second)) {
    } else {
        puzzle[filled.top().first][filled.top().second] = 0;
        unsolved.push(filled.top());
        filled.pop();
        backtrack(puzzle, unsolved, filled);
    }
    } 

}
int main() {
    int input;
    vector<vector<int>> puzzle (maxNum, vector<int>(maxNum));
    stack<pair<int,int>> unsolved;
    stack<pair<int,int>> filled;
    int coutNum = 1;

    //filling in 2D vector puzzle
    for (int i = 0; i < maxNum; i++) {
         for(int k = 0; k < maxNum; k++) {
            cin >> input;
            puzzle[i][k] = input;
            if (input == 0) {
                unsolved.push(make_pair(i,k));
            }
         }
    }
    //filling in puzzle and bactracking if the path chosen is incorrect
    while(!unsolved.empty()) {
        if(addToPuzzle(puzzle,unsolved.top().first,unsolved.top().second)) {
            filled.push(unsolved.top());
            unsolved.pop();
    } else {
            backtrack(puzzle, unsolved, filled);
    }
    }
    //display solved puzzle
    for(int i = 0; i < maxNum; i++) {
        for(int k = 0; k < maxNum; k++) {
            cout << puzzle[i][k] << " ";
        }
        cout<<endl;
    }

    


    return 0;
}
