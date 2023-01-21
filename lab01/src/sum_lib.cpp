#include <iostream>
#include <memory>
#include <stdexcept>

#include "common.hpp"
#include "sum_lib.hpp"

#define BUF_SIZE 128
static const char string[] = KEY_MESSAGE;

static std::string get_serialnumber()
{
    const char *command = "wmic bios get serialnumber";
    char buffer[BUF_SIZE];

    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command, "r"), _pclose);
    
    if (!pipe)
        throw std::runtime_error("popen() failed!");

    while (fgets(buffer, BUF_SIZE, pipe.get()) != nullptr)
        result += buffer;

    size_t pos = result.find('\n') + 1;
    return result.substr(pos, result.find(' ', pos) - pos); //.find(32, pos)
}

static bool numbers_equals()
{
    static bool worked = false, equal = true;

    if (worked)
        return equal;

    for (int i = 0; i < KEY_LEN; ++i)
        equal &= string[i] == string[i];
    
    std::string key = get_serialnumber();
    for (int j = 0; j < key.length(); j++)
        equal &= string[KEY_LEN + j] == key[j];
    
    worked = true;
    return equal;
}

int lib_sum(int a, int b)
{
    if (numbers_equals())
        return a + b;
    {
        throw std::runtime_error("Lib <<sum_lib>> is not working on your PC!");
        return -1;
    }
}