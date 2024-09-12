#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main()
{
    int arr[] = {1, 9, 3};
    int *ptr = arr;
    int * ptr2 = new int(8);
    cout << ptr[2];
    cout << ptr2[4];
}