/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

#define PII pair<int,int>
#define F first
#define S second

#define ALL(x) (x).begin(), (x).end()

/**
 *
 *  Multiple Pattern Matching using Burrows Wheeler Transform
 *  =========================================================
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

struct BWT{
    string text;
    string bwt;

    vector<int> first_occurence; // first occurence of each character in first column
    vector<int> first_to_last_mapping;
    vector<int> last_to_first_mapping;
    vector<vector<int>> tally_count; // tally count of each character

    BWT(string text){
        this->text = text;
        this->bwt = buildBWT();
        precompute();
    }

    string buildBWT(){
        vector<int> sa = SuffixArray(text).sa;

        string ret = "";

        for(int i=0;i<sa.size();i++){
            if(sa[i] == 0)
                ret += "$";
            else
                ret += text[sa[i]-1];
        }

        return ret;
    }

    string inverse_bwt(string l)
    {
        string f = l;
        sort(ALL(f));

        int n = l.size();

        vector<int> p = first_to_last_mapping;

        int k = 0;
        string ret = "";

        for (int i = 0; i < n; i++)
        {
            ret += f[p[k]];
            k = p[k];
        }

        return ret;
    }

    // create last to first, first to last, and count array
    void precompute()
    {
        int n = bwt.size();

        vector<int> cnt(256);
        for (int i = 0; i < n; i++)
            cnt[bwt[i]]++;

        vector<int> pos(256); // starting position of each character in f
        pos[0] = 0;
        for (int i = 1; i < 256; i++)
            pos[i] = pos[i - 1] + cnt[i - 1]; 

        first_occurence = pos;

        vector<int> p(n); // p[i] = position of ith character of f in l
        for (int i = 0; i < n; i++)
        {
            p[pos[bwt[i]]] = i;
            pos[bwt[i]]++; // update starting position
        }

        first_to_last_mapping = p;
        last_to_first_mapping = vector<int>(n);

        for (int i = 0; i < n; i++)
            last_to_first_mapping[p[i]] = i;

        // count array
        vector<vector<int>> c(256, vector<int>(n + 1));
        for (int i = 0; i < n; i++)
            c[bwt[i]][i+1]++;

        for (int i = 0; i < 256; i++)
            for (int j = 1; j <= n; j++)
                c[i][j] += c[i][j - 1];
        
        tally_count = c;
        
        // // print non zero count array
        // for (int i = 0; i < 256; i++)
        // {
        //     if(c[i][n-1] == 0)
        //         continue;
        //     cout << (char)i << " : ";
        //     for (int j = 0; j <= n; j++)
        //         cout << c[i][j] << " ";
        //     cout << endl;
        // }
    }

    PII match(string pattern)
    {
        string l = bwt;
        string f = l;
        sort(ALL(f));

        int n = l.size();
        int m = pattern.size();

        int top = 0, bottom = n - 1;

        while(top <= bottom)
        {
            if(m > 0)
            {
                char symbol = pattern[m-1];
                m--;

                int new_top = -1, new_bottom = -1;

                for(int i=top;i<=bottom;i++) // if position in [top,bottom] has symbol in "l"
                {
                    if(l[i] == symbol) 
                    {
                        if(new_top == -1)
                            new_top = i;
                        new_bottom = i;
                    }
                }

                if(new_top == -1) // no occurence
                    return {-1,-1};

                top = last_to_first_mapping[new_top];
                bottom = last_to_first_mapping[new_bottom];
            }
            else
            {
                return {top,bottom};
            }
        }

        return {-1,-1};
    }

    PII match_optimized(string pattern)
    {
        string l = bwt;
        string f = l;
        sort(ALL(f));

        int n = l.size();
        int m = pattern.size();

        int top = 0, bottom = n - 1;

        while(top <= bottom)
        {
            if(m > 0)
            {
                char symbol = pattern[m-1];
                m--;

                top = first_occurence[symbol] + tally_count[symbol][top];
                bottom = first_occurence[symbol] + tally_count[symbol][bottom+1] - 1;

                // cout << top << " " << bottom << endl;

                if(top > bottom) // no occurence
                    return {-1,-1};

            }
            else
            {
                return {top,bottom};
            }
        }

        return {-1,-1};
    }
};

int main()
{
    // string text = "abaaba";
    // BWT bwt(text);
    // string ret = bwt.bwt;
    // cout<<"Burrows Wheeler Transform of "<<text<<" is "<<ret<<endl;
    // cout<<"Inverse BWT of "<<ret<<" is "<<bwt.inverse_bwt(ret)<<endl;

    string text = "panamabananas";
    BWT bwt(text);
    string ret = bwt.bwt;
    cout<<"Burrows Wheeler Transform of "<<text<<" is "<<ret<<endl;
    cout<<"Inverse BWT of "<<ret<<" is "<<bwt.inverse_bwt(ret)<<endl;

    string pattern = "ana";
    PII match_ret = bwt.match_optimized(pattern);
    if (match_ret.first == -1)
        cout << "Pattern not found" << endl;
    else
        cout << "Pattern found at positions " << match_ret.first << " to " << match_ret.second <<" of first column"<< endl;

    return 0;
}
