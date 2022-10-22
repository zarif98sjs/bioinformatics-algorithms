/* Which of the favors of your Lord will you deny? */

#include <bits/stdc++.h>
using namespace std;

vector<string> motif_enumeration(vector<string>dna, int k,int d)
{
    vector<string> patterns;
    int n = dna.size();

    // for each dna
    for(int i=0;i<n;i++)
    {
        // for each k-mer in dna
        for(int j=0;j<=dna[i].size()-k;j++)
        {
            string pattern = dna[i].substr(j,k);
            // for each other dna

            int count = 0;
            for(int l=0;l<n;l++)
            {
                if(l==i) continue;
                // for each k-mer in other dna
                for(int m=0;m<=dna[l].size()-k;m++)
                {
                    string pattern2 = dna[l].substr(m,k);
                    int hamming_distance = 0;
                    for(int o=0;o<k;o++)
                    {
                        if(pattern[o]!=pattern2[o]) hamming_distance++;
                    }

                    // pattern2 differs from pattern by at most d mismatches
                    if(hamming_distance<=d)
                    {
                        count++;
                        break;
                    }
                }
            }

            // pattern2 differs from pattern by at most d mismatches in all other dna
            if(count==n-1)
            {
                patterns.push_back(pattern);
                break;
            }
        }
    }
    

    // remove duplicates from patterns
    sort(patterns.begin(),patterns.end());
    patterns.erase(unique(patterns.begin(),patterns.end()),patterns.end());

    return patterns;
}

void capitalize_inside_dna(vector<string> dna,string pattern)
{
    vector<string> new_dna = dna;
    // capitalize pattern in dna
    for(int i=0;i<dna.size();i++)
    {
        for(int j=0;j<=dna[i].size()-pattern.size();j++)
        {
            string pattern2 = dna[i].substr(j,pattern.size());
            if(pattern2==pattern)
            {
                for(int k=j;k<j+pattern.size();k++)
                {
                    new_dna[i][k] = toupper(dna[i][k]);
                }
            }
        }
    }

    // print all dna
    for(int i=0;i<new_dna.size();i++)
    {
        cout << new_dna[i] << endl;
    }
}


int main()
{

    vector<string>dna = {"atgaccgggatactgatAAAAAAAAGGGGGGGggcgtacacattagataaacgtatgaagtacgttagactcggcgccgccg",
                         "acccctattttttgagcagatttagtgacctggaaaaaaaatttgagtacaaaacttttccgaataAAAAAAAAGGGGGGGa",
                         "tgagtatccctgggatgacttAAAAAAAAGGGGGGGtgctctcccgatttttgaatatgtaggatcattcgccagggtccga",
                         "gctgagaattggatgAAAAAAAAGGGGGGGtccacgcaatcgcgaaccaacgcggacccaaaggcaagaccgataaaggaga",
                         "tcccttttgcggtaatgtgccgggaggctggttacgtagggaagccctaacggacttaatAAAAAAAAGGGGGGGcttatag",
                         "gtcaatcatgttcttgtgaatggatttAAAAAAAAGGGGGGGgaccgcttggcgcacccaaattcagtgtgggcgagcgcaa",
                         "cggttttggcccttgttagaggcccccgtAAAAAAAAGGGGGGGcaattatgagagagctaatctatcgcgtgcgtgttcat",
                         "aacttgagttAAAAAAAAGGGGGGGctggggcacatacaagaggagtcttccttatcagttaatgctgtatgacactatgta",
                         "ttggcccattggctaaaagcccaacttgacaaatggaagatagaatccttgcatAAAAAAAAGGGGGGGaccgaaagggaag",
                         "ctggtgagcaacgacagattcttacgtgcattagctcgcttccggggatctaatagcacgaagcttAAAAAAAAGGGGGGGa"};

    // convert all to small letters
    for(int i=0;i<dna.size();i++)
    {
        for(int j=0;j<dna[i].size();j++)
        {
            dna[i][j] = tolower(dna[i][j]);
        }
    }

    int k = 15;
    int d = 0;

    vector<string> patterns = motif_enumeration(dna,k,d);

    // print patterns
    for(int i=0;i<patterns.size();i++)
    {
        cout << patterns[i] << endl;
    }

    capitalize_inside_dna(dna,patterns[0]);

    return 0;
}