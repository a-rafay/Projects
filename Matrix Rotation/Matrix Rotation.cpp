/* 

You are given a 2D matrix, a, of dimension MxN and a positive integer R. You have to rotate the matrix R times and print the resultant matrix. Rotation should be in anti-clockwise direction.

Input Format 
First line contains three space separated integers, M, N and R, where M is the number of rows, N is number of columns in matrix, and R is the number of times the matrix has to be rotated. 
Then M lines follow, where each line contains N space separated positive integers. These M lines represent the matrix.

Output Format 
Print the rotated matrix.

Constraints 
2 <= M, N <= 300 
1 <= R <= 10^9 
min(M, N) % 2 == 0 
1 <= aij <= 10^8, where i ∈ [1..M] & j ∈ [1..N]

Sample Input

4 4 1
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
Sample Output

2 3 4 8
1 7 11 12
5 6 10 16
9 13 14 15
		
		Created by: Abdur Rafay		04-18-2016  12:59PM

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() { 
    int m,n,r,i,j,rot;
    cin >> m >> n >> r;
    int arr[m][n];
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) cin >> arr[i][j];

    for (rot = 0; rot < r; rot++) 
    {
        int row1 = 0, col1 = 0, row2 = m, col2 = n,  k;
        while (row2 > m/2 && col2 > n/2) {
            
            int temp = arr[row1][col1];
            for (k = col1; k < col2-1; k++) arr[row1][k] = arr[row1][k+1];

            int temp2 = arr[row2-1][col1];
            for (k = row2-1; k > row1+1; k--) arr[k][col1] = arr[k-1][col1];

            arr[k][col1] = temp;
            temp = arr[row2-1][col2-1];
            for (k = col2-1; k > col1+1; k--) arr[row2-1][k] = arr[row2-1][k-1];

            arr[row2-1][col1+1] = temp2;
            for (k = row1; k < row2-1; k++) arr[k][col2-1] = arr[k+1][col2-1];

            arr[row2-2][col2-1] = temp;
            row1++; col1++;
            row2--; col2--;
        }    
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) cout<<arr[i][j]<<" ";
        cout<<endl;    
        
    return 0;
}
