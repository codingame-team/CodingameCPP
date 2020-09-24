#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

/**
 * Remove connected regions of the same color to obtain the best score.
 **/


// Inspired from CPP program to print the largest
// connected component in a grid
// https://www.geeksforgeeks.org/largest-connected-component-on-a-grid/

const int n = 15; // lignes
const int m = 15; // colonnes

// stores information about which cell
// are already visited in a particular BFS
int visited[n][m];

// result stores the final result grid
int result[n][m];

// stores the count of cells in the largest
// connected component
int COUNT;

// Function to change coordinate system
void trans_coord(int *x, int *y)
{
    int bufX, bufY;
    bufX = *x; bufY = *y;
    *x = bufY ; *y = n - 1 - bufX;
}
// Function checks if a cell is valid i.e it
// is inside the grid and equal to the key
bool is_valid(int x, int y, int key, int input[n][m])
{
    //trans_coord(&x, &y);
    if (x < n && y < m && x >= 0 && y >= 0 && input[x][y] != -1) {
        if (visited[x][y] == false && input[x][y] == key)
            return true;
        else
            return false;
    }
    else
        return false;
}

// BFS to find all cells in
// connection with key = input[i][j]
void BFS(int x, int y, int i, int j, int input[n][m])
{
    //trans_coord(&i, &j);
    //trans_coord(&x, &y);
    // terminating case for BFS
    if (x != y)
        return;
    
    visited[i][j] = 1;
    COUNT++;
    
    // x_move and y_move arrays
    // are the possible movements
    // in x or y direction
    int x_move[] = { 0, 0, 1, -1 };
    int y_move[] = { 1, -1, 0, 0 };
    
    // checks all four points connected with input[i][j]
    for (int u = 0; u < 4; u++)
        if (is_valid(i + y_move[u], j + x_move[u], x, input))
            BFS(x, y, i + y_move[u], j + x_move[u], input);
}

// called every time before a BFS
// so that visited array is reset to zero
void reset_visited()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            //trans_coord(&i, &j);
            visited[i][j] = 0;
        }
}

// If a larger connected component
// is found this function is called
// to store information about that component.
void reset_result(int key, int input[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //trans_coord(&i, &j);
            if (visited[i][j] && input[i][j] == key)
                result[i][j] = visited[i][j];
            else
                result[i][j] = 0; //false
        }
    }
}

// function to choose a tile in the result region
int *choose_tile()
{
    int *t = new int[2];
    bool loop = true;
    for (int i = 0; i < n && loop; i++) {
        for (int j = 0; j < m && loop; j++) {
            //trans_coord(&i, &j);
            if (result[i][j])
                cerr << "i = " << *t << " j = " << *(t+1) << endl;
                *t = i; *(t+1) = j;
                loop = false;
        }
    }
    return t;
}

// function to print the result 
void print_result(int res)
{
    cerr << "The largest connected "
    << "component of the grid is :" << res << "\n";
    
    // prints the largest component
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //trans_coord(&i, &j);
            if (result[j][n-1-i]) {
                cerr << result[j][n-1-i] << " ";
                //cerr << i << " " << j;
            }
            else
                //cerr << result[i][j] << " ";
                cerr << ". ";
        }
        cerr << "\n";
    }
}

// function to calculate the largest connected
// component
int computeLargestConnectedGrid(int input[n][m])
{
    int current_max = INT_MIN;

    //cerr << "INT_MIN = " << INT_MIN <<endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //trans_coord(&i, &j);
            reset_visited();
            COUNT = 0;
            
            // checking cell to the right
            if (j + 1 < m)
                BFS(input[i][j], input[i][j + 1], i, j, input);
            
            // updating result
            if (COUNT >= current_max) {
                current_max = COUNT;
                reset_result(input[i][j], input);
            }
            reset_visited();
            COUNT = 0;
            
            // checking cell downwards
            if (i + 1 < n)
                BFS(input[i][j], input[i + 1][j], i, j, input);
            
            // updating result
            if (COUNT >= current_max) {
                current_max = COUNT;
                reset_result(input[i][j], input);
            }
        }
    }
    cerr << "current_max = " << current_max <<endl;
    print_result(current_max);    
    return(current_max);
}


int main()
{
    bool start = true;
    int input[n][m];
    int max_tiles = 0;
    int x, y;
    // game loop
    while (1) {
        auto begin = chrono::steady_clock::now();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int color; // Color of the tile
                cin >> color; cin.ignore();
                //trans_coord(&i, &j);
                input[j][n-1-i] = color;
                //cerr << color;
            }
            cerr << endl;
        }
        max_tiles = computeLargestConnectedGrid(input);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        // string message = "time: " + std::to_string(time) + " ms";
        // string alert;
        // if (!start) {
        //     if (40 < time && time <= 50)
        //         alert = "Long near 50ms";
        //     else if (time <= 40)
        //         alert = "Good <= 50ms";
        //     else
        //         alert = "Bad > 50ms";
        // }
        // else {
        //     start = false;
        //     if (time/1000 <= 20) 
        //         alert = "Good <= 20s";
        //     else
        //         alert = "Bad > 20s";
        // }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int *t = choose_tile();
        x = *t ; y = *(t+1);
        trans_coord(&x, &y);
        //cout << t[0] << " " << t[1] << " " << alert << "\\n" << message << endl; // Selected tile "x y [message]".
        cout << x << " " << y; // Selected tile "x y [message]".
        cout << " x=" << x << " y=" << y << "\\n" << "lrl=" << max_tiles << endl; 
        delete[] t;
    }
}