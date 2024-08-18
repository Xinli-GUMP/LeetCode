#include <iostream>
#include <string>
#include <vector>

std::vector< int > computeLPS(const std::string &pat)
{
    std::vector< int > lps(pat.size(), 0);
    int length = 0;  // Length of the previous longest prefix suffix
    int i = 1;

    while (i < pat.size())
    {
        if (pat[i] == pat[length])
        {
            length++;
            lps[i] = length;
            i++;
        } else
        {
            if (length != 0)
            {
                length = lps[length - 1];  // Use the previous LPS value
            } else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMPSearch(const std::string &txt, const std::string &pat)
{
    int n = txt.size();
    int m = pat.size();
    std::vector< int > lps = computeLPS(pat);

    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]

    while (i < n)
    {
        if (pat[j] == txt[i])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            std::cout << "Found pattern at index " << i - j << std::endl;
            j = lps[j - 1];  // Continue to check for more occurrences
        } else if (i < n && pat[j] != txt[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            } else
            {
                i++;
            }
        }
    }
}

int main()
{
    std::string txt = "ABABDABACDABABCABAB";
    std::string pat = "ABABCABAB";
    KMPSearch(txt, pat);
    return 0;
}
