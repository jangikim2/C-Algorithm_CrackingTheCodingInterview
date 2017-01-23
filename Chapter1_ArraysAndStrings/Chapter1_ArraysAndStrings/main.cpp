//
//  main.cpp
//  Chapter1_ArraysAndStrings
//
//  Created by JaeYoon Kim on 22/01/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

static bool isUniqueChars1(std::string str);
static bool isUniqueChars2(std::string str);
void reverse(char *str);
static void removeDuplicates1(char str[]);
static void removeDuplicates2(char str[]);
bool anagram1(std::string s, std::string t);
static bool anagram2(std::string s, std::string t);
static void ReplaceFun(char str[], int length);
static void rotate(int **matrix, int n);
static void setZeros(int **matrix, int rowindex, int columnindex);
static string::size_type isRotation(std::string s1, std::string s2);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //1.1
    std::string s_duplicate = "aacd";
    if(!isUniqueChars1(s_duplicate))
        std::cout << "There is a duplicate character\n";
    else
        std::cout << "There is not a duplicate character\n";
    
    //1.2
    std::string s1 = "gotcha";
    //std::string s1 = "Hello, world";
    char* str = new char[s1.length() + 1];
    strcpy(str, s1.c_str());
    reverse(str);
    delete[] str;
    
    //1.3
    //Contiguous duplicate
    //char testDuplicate [256] = "abcd";
    //char testDuplicate [256] = "aaaa";
    //char testDuplicate [256] = "";
    //char testDuplicate [256] = "aaaabbbb";
    char testDuplicate [256] = "abababa";
    //Non-contiguous duplicate
    removeDuplicates1(testDuplicate);
    removeDuplicates2(testDuplicate);
    
    //1.4
    std::string s ("Kim");
    std::string t ("Kim");
    char testArray [256] = "Jae Yoon Kim";
    if( anagram1(s, t))
        std::cout << "1.Same string!\n";
    else
        std::cout << "1.Differnet string!\n";
    
    
    if( anagram2(s, t))
        std::cout << "2.Same string!\n";
    else
        std::cout << "2.Differnet string!\n";
    
    //1.5
    ReplaceFun(testArray, 12);
    
    //1.6
    int **marray;
    marray = new int *[3];
    for (int i = 0; i < 10; i++) {
        marray[i] = new int[3];
    }
    marray[0][0] = 1;
    marray[0][1] = 2;
    marray[0][2] = 3;
    marray[1][0] = 4;
    marray[1][1] = 5;
    marray[1][2] = 6;
    marray[2][0] = 7;
    marray[2][1] = 8;
    marray[2][2] = 9;
    
    
    rotate(marray, 3);
    
    std::cout << "0 0 " << marray[0][0] << "\n";
    std::cout << "0 1 " << marray[0][1] << "\n";
    std::cout << "0 2 " << marray[0][2] << "\n";
    std::cout << "1 0 " << marray[1][0] << "\n";
    std::cout << "1 1 " << marray[1][1] << "\n";
    std::cout << "1 2 " << marray[1][2] << "\n";
    std::cout << "2 0 " << marray[2][0] << "\n";
    std::cout << "2 1 " << marray[2][1] << "\n";
    std::cout << "2 2 " << marray[2][2] << "\n";
    //int multiarray[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    //rotate(multiarray, 3);
    
    //1.7
    marray[0][0] = 1;
    marray[0][1] = 2;
    marray[0][2] = 0;
    marray[1][0] = 4;
    marray[1][1] = 5;
    marray[1][2] = 6;
    marray[2][0] = 7;
    marray[2][1] = 8;
    marray[2][2] = 9;
    setZeros(marray, 3, 3);
    
    std::cout << "0 0 " << marray[0][0] << "\n";
    std::cout << "0 1 " << marray[0][1] << "\n";
    std::cout << "0 2 " << marray[0][2] << "\n";
    std::cout << "1 0 " << marray[1][0] << "\n";
    std::cout << "1 1 " << marray[1][1] << "\n";
    std::cout << "1 2 " << marray[1][2] << "\n";
    std::cout << "2 0 " << marray[2][0] << "\n";
    std::cout << "2 1 " << marray[2][1] << "\n";
    std::cout << "2 2 " << marray[2][2] << "\n";
    
    
    //1.8
    std::string string2 ("apple");
    std::string string1 ("pleap");
    //std::string string1 ("ppale");
    std::size_t found = isRotation(string1, string2);
    if (found!=std::string::npos)
        std::cout << "string2 found at: " << found << '\n';
    else
        std::cout << "string2 is not found." << '\n';
    
    return 0;
}


//1.1
static bool isUniqueChars2(std::string str) {
    bool char_set[256];
    
    for(int i = 0; i < str.length(); i++) {
        int val = str.at(i);
        if(char_set[val]) return false;
        char_set[val] = true;
     }
    return true;
}

static bool isUniqueChars1(std::string str) {
    int checker = 0;
    
    for(int i = 0; i < str.length(); i++) {
        int val = str.at(i) - 'a';
        if((checker & (1 << val)) > 0) return false;
        checker |= (1 << val);
    }
    return true;
}

//1.2
void reverse(char *str) {
    char * end = str;
    char tmp;
    if (str) {
        while (*end) {
            ++end;
        }
        --end;
        while(str < end) {
            tmp = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
}


//1.3
static void removeDuplicates1(char str[]) {
    int len = (unsigned)strlen(str);
    if(len == 0) return;
    if(len < 2) return;
    
    int tail = 1;
    
    for(int i =1; i < len; ++i) {
        int j;
        for(j=0; j < tail; ++j) {
            if(str[i] == str[j]) break;
        }
        if(j == tail) {
            str[tail] = str[i];
            ++tail;
        }
    }
    
    str[tail] = 0;
}

static void removeDuplicates2(char str[]) {
    int len = (unsigned)strlen(str);
    if(len == 0) return;
    if(len < 2) return;
    
    bool hit[256];
    
    for(int i = 0; i < 256; ++i) {
        hit[i] = false;
    }
    
    hit[str[0]] = true;
    int tail = 1;
    
    for(int i =1; i < len; ++i) {
        if(!hit[str[i]]) {
            str[tail] = str[i];
            ++tail;
            hit[str[i]] = true;
        }
    }
    
    str[tail] = 0;
}

// 1.4
bool anagram1(std::string s, std::string t) {
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    
    if( s == t)
        return true;
    else
        return false;
}


static bool anagram2(std::string s, std::string t) {
    if(s.length() != t.length())
        return false;
    int letters [256] = {0,};
    int num_unique_chars = 0;
    int num_completed_t = 0;
    
    //char s_array [s.length() + 1];
    char s_array [s.length()];
    strcpy(s_array, s.c_str());
    
    for(char c: s_array)
    {
        if(letters[c] == 0) ++num_unique_chars;
        ++letters[c];
    }
    for (int i = 0; i < t.length(); ++i) {
        int c = (int) t.at(i);
        if (letters[c] == 0) {
            return false;
        }
        --letters[c];
        if(letters[c] == 0) {
            ++num_completed_t;
            if(num_completed_t == num_unique_chars) {
                return i == t.length() - 1;
            }
        }
    }
    return false;
}

//1.5
static void ReplaceFun(char str[], int length)
{
    int spaceCount = 0, newLength, i = 0;
    for(i=0; i < length; i++) {
        if(str[i] == ' ') {
            spaceCount++;
        }
    }
    newLength = length + spaceCount * 2;
    str[newLength] = '\0';
    for(i = length - 1; i >= 0; i--) {
        if(str[i] == ' ') {
            str[newLength - 1] = '0';
            str[newLength - 2] = '2';
            str[newLength - 3] = '%';
            newLength = newLength - 3;
        } else {
            str[newLength - 1] = str[i];
            newLength = newLength - 1;
        }
    }
}

//1.6
static void rotate(int **matrix, int n) {
//static void rotate(int matrix[][3], int n) {
    for (int layer = 0; layer < n; ++layer) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            int top = matrix[first][i];
            
            matrix[first][i] = matrix[last-offset][first];
            
            matrix[last-offset][first] = matrix[last][last - offset];
            
            matrix[last][last - offset] = matrix[i][last];
            
            matrix[i][last] = top;
        }
    }
}

//1.7
static void setZeros(int **matrix, int rowindex, int columnindex) {
    //int rowindex = sizeof matrix / sizeof matrix[0];
    //int columnindex = sizeof matrix[0];
    int row [rowindex];
    int column [columnindex];
    
    for(int i = 0; i < rowindex; ++i)
        row[i] = 0;
    
    for(int i = 0; i < columnindex; ++i)
        column[i] = 0;
    
    
    for (int i = 0; i < rowindex; i++) {
        for (int j = 0; j < columnindex; j++) {
            if(matrix[i][j] == 0) {
                row[i] = 1;
                column[j] = 1;
            }
        }
    }
    
    std::cout << "\n" << "\n";
    std::cout << "row 0 " << row[0] << "\n";
    std::cout << "row 1 " << row[1] << "\n";
    std::cout << "row 2 " << row[2] << "\n";
    std::cout << "column 0 " << column[0] << "\n";
    std::cout << "column 1 " << column[1] << "\n";
    std::cout << "column 2 " << column[2] << "\n";

    
    for (int i = 0; i < rowindex; i++) {
        for (int j = 0; j < columnindex; j++) {
            if(row[i] == 1 || column[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }
}

//1.8
static string::size_type isRotation(std::string s1, std::string s2) {
    int len = (unsigned)s1.length();
    if(len == s2.length() && len > 0) {
        std::string s1s1 = s1 + s1;
        return s1s1.find(s2);
    }
    
    return std::string::npos;
}