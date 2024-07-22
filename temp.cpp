#include <iostream>
#include <vector>

void mergeVectors(std::vector< std::vector< int > > &vec, size_t i, size_t j)
{
    if (i >= vec.size() || j >= vec.size() || i == j)
    {
        std::cerr << "Invalid indices or same indices for merge." << std::endl;
        return;
    }

    // Move elements of vec[j] to vec[i]
    vec[i].insert(vec[i].end(), std::make_move_iterator(vec[j].begin()),
                  std::make_move_iterator(vec[j].end()));

    // Optionally, we can clear the j-th vector if it's no longer needed
    vec.erase(vec.begin() + j);
}

int main()
{
    std::vector< std::vector< int > > vec = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    mergeVectors(vec, 0, 1);

    // Print the result
    for (const auto &innerVec : vec)
    {
        for (int num : innerVec)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
