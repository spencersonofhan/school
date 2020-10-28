#include "WordTree.hpp"
#include "rlutil.h"

void printThis(std::string words, int yCoord);

void printThis(std::string words, int yCoord)
{
    for (uint8_t j = 0; j < words.length(); j++)
    {
        rlutil::locate(j, yCoord);
        rlutil::setChar(words[j]);
    }
}

int main()
{
    auto wordTree = readDictionary("dictionary.txt");

    // THIS RETURNS AN ASCII CODE
    std::vector<char> wordSoFar;
    rlutil::cls();
    printThis("--- prediction ---", 3);
    bool isTyping = true;
    while (isTyping)
    {
        auto letter = rlutil::getkey();
        rlutil::cls();

        if (letter < 97 || letter > 122)
        {
            std::cout << letter << std::endl;
        }
        else
        {
            wordSoFar.push_back(wordTree->getLetter(letter - 97));
        }

        for (uint8_t i = 0; i < wordSoFar.size(); i++)
        {
            rlutil::locate(i + 1, 1);
            rlutil::setChar(wordSoFar[i]);
        }

        printThis("--- prediction ---", 3);

    }
}
