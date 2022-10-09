/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

/**
 * 
 *  O(n*m) time complexity
 * 
 **/

bool match(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    for (int i = 0; i <= n - m; i++) {
        bool found = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
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