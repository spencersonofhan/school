#include "WordTree.hpp"

int main()
{
    std::string test = "howdy";
    auto wordTree = std::make_shared<WordTree>();
    wordTree->add(test);
    if (wordTree->find("howdy"))
    {
        std::cout << "$BIGMONEY$" << std::endl;
    }
    else
    {
        std::cout << "No more money" << std::endl;
    }

    // auto wordTree = readDictionary();
    // std::cout << wordTree->getLetter(1) << std::endl;
}
