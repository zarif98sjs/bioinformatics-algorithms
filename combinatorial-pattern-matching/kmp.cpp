/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

// to understand algorithm intuition, refer to https://www.scaler.com/topics/data-structures/kmp-algorithm/

/**
 * 
 *  LPS array : Longest Proper Prefix which is also Suffix
 *  O(m) time complexity
 * 
 **/
vector<int> computeLPSArray(string pattern) {

    int M = pattern.size();
    vector<int> lps(M);
    
    int len = 0; // length of previous longest proper prefix that is also a suffix
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/**
 * 
 *  O(m) time complexity for computing LPS array
 *  O(n) [actually O(2n)] time complexity for matching using KMP
 * 
 **/

bool match(string text, string pattern) {

    vector<int> lps = computeLPSArray(pattern);

    int n = text.size();
    int m = pattern.size();
    int i = 0; // index for text [ *** this will never go back to the left like in bruteforce *** ]
    int j = 0; // index for pattern
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            return true;
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; 
                // this is the idea, instead of fully resetting j to 0, 
                // we can use the lps array to jump to the next possible position considering what's already matched
            } else {
                i++;
            }
        }
    }
    return false;
}

int main()
{
    string text = "ababac";
    string pattern = "abac";
    cout << ( match(text, pattern) == true ? "true" : "false" ) << endl;

    return 0;
}