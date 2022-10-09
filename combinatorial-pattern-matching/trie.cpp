/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

/** 
 * 
 *  Multiple Pattern Matching using Trie
 *  ====================================
 * 
 *  First create Trie(Patterns) using all the query patterns.
 *  When inserting a pattern into Trie, we mark the last node of the pattern with a marker.
 * 
 *  After that, for each starting positions of Text, check if there is a match with a marker in Trie 
 * 
 **/

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }

    void insert(string pattern) {
        TrieNode* curr = this;
        for (char c : pattern) {
            if (curr->children.find(c) == curr->children.end()) { // if node alredy not present
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    bool match(string text) {
        
        TrieNode* curr = this;
        string pattern = "";

        for (char c : text) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }

            pattern += c;
            curr = curr->children[c];

            if(curr->isEndOfWord){
                cout << "Pattern found " << pattern << endl;
            }
        }

        if(curr->isEndOfWord){
            cout << "Pattern found " << pattern << endl;
        }

        return curr->isEndOfWord;
    }

};

int main()
{   
    TrieNode* root = new TrieNode();
    vector<string> patterns = {"ananas", "and", "antenna", "banana", "bandana", "nab", "nana", "pan", "pantry"};
    for (string pattern : patterns) {
        root->insert(pattern);
    }

    string text = "panamabananas";

    for (int i = 0; i < text.size(); i++) {
        string suffix = text.substr(i);
        cout<< ">> current text " << suffix << endl;
        root->match(suffix);
    }

    return 0;
}