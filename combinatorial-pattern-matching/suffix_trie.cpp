/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

/** 
 * 
 *  Multiple Pattern Matching using Suffix Trie
 *  ====================================
 * 
 *  Instead of calculating Trie(Patterns), we calculate Trie(Text) by creating Trie from all suffix of the Text. 
 *  This way we can reduce the memory complexity from the previous method as we don't have to store all the patterns.
 * 
 **/

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }

    void insert(string text) {
        TrieNode* curr = this;
        for (char c : text) {
            if (curr->children.find(c) == curr->children.end()) { // if node alredy not present
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    bool match(string pattern)
    {
        TrieNode* curr = this;
        for (char c : pattern) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return true;
    }
};

int main()
{
    string text = "panamabananas";

    TrieNode* root = new TrieNode();
    for (int i = 0; i < text.size(); i++) {
        string suffix = text.substr(i);
        root->insert(suffix);
    }

    vector<string> patterns = {"ananas", "and", "antenna", "banana", "bandana", "nab", "nana", "pan", "pantry"};
    for (string pattern : patterns) {
        if(root->match(pattern)){
            cout << "Pattern found " << pattern << endl;
        }
    }

    return 0;
}