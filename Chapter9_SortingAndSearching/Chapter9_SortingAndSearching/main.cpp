//
//  main.cpp
//  Chapter9_SortingAndSearching
//
//  Created by JaeYoon Kim on 8/12/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//9.1
void merge(int *a, int *b, int n, int m) {
    int k = m + n - 1; // Index of last location of array b
    int i = n - 1; // Index of last element in array a
    int j = m - 1; // Index of last element in array b
    
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
//9.2
//https://sites.google.com/site/spaceofjameschen/home/sort-and-search/sort-an-array-of-strings-anagram
bool is_anagram(string &s1, string &s2)
{
    vector<char> v1, v2;
    
    v1.assign(s1.begin(),s1.end());
    v2.assign(s2.begin(),s2.end());
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    return (v1 == v2);
}

void print_strings(vector<string> &v)
{
    copy(v.begin(), v.end(),ostream_iterator<string>(cout, " "));
    cout << endl;
}

void sort_strings(vector<string> &v)
{
    sort(v.begin(), v.end());
    
    //cout << "after sorting v" << endl;
    //print_strings(v);
    
    int i, j;
    int len = v.size();
    
    for(i = 0; i < len ;i ++ ){
        for( j = i + 1; j < len; j ++){
            if(is_anagram(v.at(i), v.at(j))){
                string s = v.at(j);
                v.erase(v.begin() + j);
                i ++;
                v.insert(v.begin() + i, s);
            }
        }
    } 
}

//9.3
int search(int a[], int l, int u, int x){
    while (l <= u) {
        int m = (l+u) / 2;
        if (x == a[m]) {
            return m;
        } else if (a[l] <= a[m]) {
            if (x > a[m]) {
                l = m + 1;
            } else if (x >= a[1]) {
                u = m - 1;
            } else {
                l = m + 1;
            }
        }
        else if (x < a[m]) u = m - 1;
        else if (x <= a[u]) l = m + 1;
        else u = m - 1;
    }
    return -1;
}

//9.5
int search952(string strings[], string str, int first, int last)
{
    while (first <= last) {
        //Ensure there is something at the end
        while (first <= last && strings[last] == "") {
            --last;
        }
        if(last < first) {
            return -1; //this block was empty, so fail
        }
        int mid = (last + first) >> 1;
        while (strings[mid] == "") {
            ++mid; // will always find one
        }
        int r = strings[mid].compare(str);
        if (r == 0) return mid;
        if (r < 0) {
            first = mid + 1;
        } else {
            last = mid -1;
        }
    }
    return -1;
}

int search951(string strings[], string str, int size) {
    if(strings == nullptr || str.empty()) return -1;
    if(str == "") {
        for(int i = 0; i < size; i++) {
            if(strings[i] == "") return i;
        }
        return -1;
    }
    
    return search952(strings, str, 0, size - 1);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //9.1
    int a[20] = {1, 3, 5, 7, 9, 11};
    int b[3] = {2, 4, 6};
        
    merge(a, b, 6, 3);
    
    for (auto item : a) {
        cout << item << endl;
    }
    
    //9.2 This is the same as the solution of James chun
    vector<string> v;
    
    v.push_back("I");
    v.push_back("yum");
    v.push_back("can");
    v.push_back("eat");
    v.push_back("I");
    v.push_back("ate");
    v.push_back("att");
    v.push_back("I");
    v.push_back("the");
    v.push_back("eel");
    v.push_back("eth");
    v.push_back("het");
    
    cout << "before sort" << endl;
    print_strings(v);
    
    sort_strings(v);
    
    cout << "after sort" << endl;
    print_strings(v);
    
    //9.3
    int arr[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int n = sizeof(arr)/sizeof(arr[0]) - 1;
    int find_n = search(arr, 0, n, 5);
    cout << "Binary search output : " << find_n << endl;
    
    //9.4 This is just skipped because of the enough explannation of textbook.
    
    //9.5
    //condition 1
    string strings[] = {"at", "","","","ball","","","car","","","dad","",""};
    string string_t = "ball";
    //string strings[] = {"at","","","","","ball","car","","","dad","",""};
    //string string_t = "ballcar";
    int find_string = search951(strings, string_t, sizeof(strings)/sizeof(strings[0]) - 1);
    cout << "Founded at : " << find_string << endl;

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
 before sort
 I yum can eat I ate att I the eel eth het
 after sort
 I I I ate eat att can eel eth het the yum
 Binary search output : 8
 Founded at : 4
 Program ended with exit code: 0
 */
