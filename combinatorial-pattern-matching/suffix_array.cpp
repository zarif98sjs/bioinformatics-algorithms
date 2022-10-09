/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

#define PII pair<int,int>
#define F first
#define S second

#define ALL(x) (x).begin(), (x).end()

/**
 *
 *  Multiple Pattern Matching using Suffix Array
 *  ============================================
 *
 **/

struct SuffixArray
{
    string s;
    vector<int> sa;

    SuffixArray(string s){
        this->s = s;
        this->sa = buildSuffixArray();
    }

    void count_sort(vector<int> &p, vector<int> &c)
    {
        int n = p.size();

        vector<int> cnt(n);

        for (auto el : c)
            cnt[el]++;

        vector<int> np(n);
        vector<int> pos(n); /// pos[i] = first empty position in bucket i

        pos[0] = 0;
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];

        for (auto el : p)
        {
            int i = c[el];   /// bucket
            np[pos[i]] = el; /// putting element in bucket
            pos[i]++;        /// empty position in bucket i increased
        }

        p = np;
    }

    vector<int> buildSuffixArray()
    {
        s += "$";

        int n = s.size();

        /// init p , c

        vector<PII> v(n);

        for (int i = 0; i < n; i++)
            v[i] = {s[i], i};
        sort(ALL(v));

        vector<int> p(n), c(n);
        for (int i = 0; i < n; i++)
            p[i] = v[i].S;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (v[i].F != v[i - 1].F)
                c[p[i]] = c[p[i - 1]] + 1;
            else
                c[p[i]] = c[p[i - 1]];
        }

        /// logN times

        int k = 0;

        while ((1 << k) < n)
        {
            for (int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;

            count_sort(p, c);

            vector<int> nc(n);

            nc[p[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                PII now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                PII prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};

                if (now != prev)
                    nc[p[i]] = nc[p[i - 1]] + 1;
                else
                    nc[p[i]] = nc[p[i - 1]];
            }

            c = nc;
            k++;
        }

        /// after all the iterations , c[i] = position of the suffix i in p

        return p;
    }

    bool match(string pattern)
    {
        int n = s.size();
        int m = pattern.size();

        int l = 0, r = n - 1;

        while (l <= r)
        {
            int mid = (l + r) / 2;

            string curr = s.substr(sa[mid], m);

            if (curr == pattern)
                return true;
            else if (curr < pattern)
                l = mid + 1;
            else
                r = mid - 1;
        }

        return false;
    }
};

int main()
{
    string text = "panamabananas";
    SuffixArray sa(text);
    
    vector<string> patterns = {"ananas", "and", "antenna", "banana", "bandana", "nab", "nana", "pan", "pantry"};

    for (string pattern : patterns) {
        if(sa.match(pattern)){
            cout << "Pattern found " << pattern << endl;
        }
    }

    return 0;
}
