//
//  main.cpp
//  Chapter9_SortingAndSearching
//
//  Created by JaeYoon Kim on 8/12/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>

using namespace std;


void merge(int *a, int *b, int n, int m) {
    int k = m + n - 1; // Index of last location of array b
    int i = n - 1; // Index of last element in array a
    int j = m - 1; // Index of last element in array b
    
    //9.1
    //Start comparing from the last element and merge a and b
    while (i >= 0 && j >= 0) {
        if(a[i] > b[j]) {
            a[k--] = a[i--];
        } else {
            a[k--] = b[j--];
        }
    }
    while (j >=0) {
        a[k--] = b[j--];
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int a[20] = {1, 3, 5, 7, 9, 11};
    int b[3] = {2, 4, 6};
        
    merge(a, b, 6, 3);
    
    for (auto item : a) {
        cout << item << endl;
    }

    return 0;
}

/* output */
/*
 Hello, World!
 1
 2
 3
 4
 5
 6
 7
 9
 11
 0
 0
 0
 0
 0
 0
 0
 0
 0
 0
 0
 Program ended with exit code: 0
 */
