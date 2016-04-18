/*
	Calculating square root of T samples from range A to B
	Example : 2
		  1 100
		  17 24
	Output: 10
		0

	Copyrights: Abdur Rafay

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() { 
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) {
        int A, B, count = 0;
        cin >> A >> B;
        bool toBreak = false;
        for (int i = A; i <= B; i++) {
            double rd = pow(i,0.5);
            int ri = pow(i,0.5);
            if (rd-ri == 0) {
                count++;
                int ri2 = ++ri;
                while (ri2 <= B){
                    ri2 = pow(ri2,2);
                    if (ri2 <= B) count++;
                    else {
                        toBreak = true;
                        break;
                    }
                    ri2 = pow(ri2,0.5);
                    ri2++;  
                }
                if (toBreak) break;
            }
            if (toBreak) break;
        }
        cout<<count<<endl;    
    }
    return 0;
}

