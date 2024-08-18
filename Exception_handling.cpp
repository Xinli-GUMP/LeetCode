#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        // 抛出一个标准异常
        throw std::runtime_error("Runtime error occurred!");
    }
    catch (const std::exception &e)
    {  // 捕获所有标准异常
        std::cout << "Caught a standard exception: " << e.what() << std::endl;
    }
    catch (...)
    {  // 捕获所有其他异常
        std::cout << "Caught an unknown exception." << std::endl;
    }

    return 0;
}
