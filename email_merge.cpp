
/*

给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素
accounts[i][0] 是 名称 (name)，其余元素是 emails 表示该账户的邮箱地址。

现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于同一个人。请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为人们可能具有相同的名称。一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。

合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是 按字符
ASCII 顺序排列 的邮箱地址。账户本身可以以 任意顺序 返回。

*/

// 解题思路：
// 题意目的要合并同一个人的所有账户，而判断是否为同一个人的唯一方式是————是否使用了相同的邮箱,
// 但是同一个人的所有账户都具有相同名称。
// 先用外层循环遍历整个容器，然后内存循环遍历每个账户中的邮箱，创建一个字符串保存当前要对比的名称，再3层循环遍历每个账户中的名称，对比是否有相同的名称，如果有，就再次对比是否有相同的邮箱，如果还有，就将当前遍历到的容器合并到上层循环正在遍历的容器中，合并时需要处理额外的相同邮箱，只保留一个，注意可能会有索引越界问题.
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

vector< vector< string > > accountsMerge(vector< vector< string > > &accounts)
{
    bool is_merged = false;
    int account_nums = accounts.size();
    for (int i = 0; i < account_nums; i++)
    {
        // sort(accounts[i].begin(), accounts[i].end());
        string name = accounts[i][0];
        unordered_set< string > emails_set(accounts[i].begin() + 1,
                                           accounts[i].end());
        for (int j = i + 1; j < account_nums; j++)
        {
            if (name == accounts[j][0])
            {
                for (string &elem : accounts[j])
                {
                    if (emails_set.find(elem) != emails_set.end())
                    {
                        accounts[i].insert(accounts[i].end(),
                                           accounts[j].begin() + 1,
                                           accounts[j].end());
                        accounts.erase(accounts.begin() + j);
                        --account_nums;
                        --j;
                        is_merged = true;
                        break;
                    }
                }
            }
        }

        sort(accounts[i].begin() + 1, accounts[i].end());
        auto uniqueEnd_ite =
            std::unique(accounts[i].begin() + 1, accounts[i].end());
        accounts[i].erase(uniqueEnd_ite, accounts[i].end());
    }
    if (is_merged)
    {
        accountsMerge(accounts);
    }

    return accounts;
}

int main(int argc, char const *argv[])
{
    vector< vector< string > > accounts = {
        {"David", "David0@m.co", "David1@m.co"},
        {"David", "David3@m.co", "David4@m.co"},
        {"David", "David4@m.co", "David5@m.co"},
        {"David", "David2@m.co", "David3@m.co"},
        {"David", "David1@m.co", "David2@m.co"}};
    accountsMerge(accounts);
    for (auto i : accounts)
    {
        for (auto j : i)
        {
            cout << j << ' ';
        }
        cout << '\n';
    }
    return 0;
}