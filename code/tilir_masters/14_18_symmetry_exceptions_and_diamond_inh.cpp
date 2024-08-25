#include <iostream>
#include <memory>
#include <sstream>

#include "gtest/gtest.h"

namespace
{

struct File
{
    int a;
    File(int a) : a{a} {}
    virtual ~File() {}
};

struct InputFile : public File
{
    int b;
    InputFile(int b) : File(b * 2), b{b} {}
};

struct OutputFile : public File
{
    int c;
    OutputFile(int c) : File(c * 3), c{c} {}
};

struct IOFile : public InputFile, public OutputFile
{
    int d;
    IOFile(int d) : InputFile(d * 5), OutputFile(d * 7), d{d} {}
};

} // namespace

TEST(rtpoly, virtinh)
{
    try
    {
        throw IOFile(11);
    }
    catch (File&)
    {
        EXPECT_EQ(1, 1);
    }
    catch (...)
    {
        EXPECT_EQ(1, 0);
    }
}