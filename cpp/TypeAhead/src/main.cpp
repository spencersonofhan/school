#include "WordTree.hpp"
#include "rlutil.h"

int main()
{
    auto wordTree = readDictionary("dictionary.txt");

    // THIS RETURNS AN ASCII CODE
    auto temp = rlutil::getkey();
    std::cout << temp << std::endl;
}
