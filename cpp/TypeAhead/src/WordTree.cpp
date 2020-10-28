#include "WordTree.hpp"


void WordTree::add(std::string word)
{
    // Gets root and checks if it's null and adds it if is
    auto currNode = roots[getFixedASCII(word[0])];
    if (currNode == NULL)
    {
        auto newNode = std::make_shared<TreeNode>();
        roots[getFixedASCII(word[0])] = newNode;
        currNode = newNode;
        if (word.length() == 1)
        {
            roots[getFixedASCII(word[0])]->isEndOfWord();
            sizeAddOne();
            return;
        }
    }

    // Adds nodes if they don't already exist
    for (std::uint8_t i = 1; i < word.length(); i++)
    {
        auto parent = currNode;
        currNode = currNode->children[getFixedASCII(word[i])];
        if (currNode == NULL)
        {
            auto newNode = std::make_shared<TreeNode>();
            parent->children[getFixedASCII(word[i])] = newNode;
            currNode = newNode;
        }
    }
    currNode->isEndOfWord();
    sizeAddOne();
}

bool WordTree::find(std::string word)
{
    // Gets the first node in the tree or adds one if there isn't one
    auto currNode = roots[getFixedASCII(word[0])];
    if (currNode == NULL)
    {
        return false;
    }

    // The search begins
    for (std::uint8_t i = 1; i < word.length(); i++)
    {
        currNode = currNode->children[getFixedASCII(word[i])];
        if (currNode == NULL)
        {
            return false;
        }
    }

    // Check if the ending node has endOfWord flagged (true)
    if (currNode->endOfWord)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> yawyeet = {"yep", "ohyes"};
    return yawyeet;
}

char WordTree::getLetter(std::uint8_t letterNum){
    return alphabet[letterNum];
}

int WordTree::getFixedASCII(char letterNum) {
    return int(letterNum) - 97;
}

std::size_t WordTree::size()
{
    return treeSize;
}

void WordTree::sizeAddOne()
{
    treeSize++;
}


std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;

        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}
