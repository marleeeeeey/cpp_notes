#include <exception>
#include <iostream>
#include <memory>

struct FileDeleter
{
    void operator()(std::FILE* f) const
    {
        if (f)
        {
            std::cout << "Closing file" << std::endl;
            std::fclose(f);
        }
        else
        {
            std::cout << "File already closed" << std::endl;
        }
    }
};

int main()
{
    try
    {
        std::cout << "Opening file" << std::endl;
        std::FILE* f = std::fopen("__temp_file_may_be_removed.txt", "w");
        std::unique_ptr<std::FILE, FileDeleter> file(f);
    }
    catch (std::exception const& e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught an unknown exception" << std::endl;
    }
}