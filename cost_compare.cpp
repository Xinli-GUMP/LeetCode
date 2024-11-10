#include <chrono>
#include <cstring>
#include <iostream>

void allocateWithTryCatch()
{
    try
    {
        char *data = new char[100];
        strcpy(data, "Test");
        delete[] data;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
    }
}

void allocateWithoutTryCatch()
{
    char *data = new char[100];
    strcpy(data, "Test");
    delete[] data;
}

int main()
{
    const int iterations = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        allocateWithoutTryCatch();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double, std::milli > durationWithoutTryCatch =
        end - start;
    std::cout << "Time taken without try-catch: "
              << durationWithoutTryCatch.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        allocateWithTryCatch();
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double, std::milli > durationWithTryCatch =
        end - start;
    std::cout << "Time taken with try-catch: " << durationWithTryCatch.count()
              << " ms" << std::endl;

    return 0;
}
