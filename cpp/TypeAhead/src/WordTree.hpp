#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <memory>
#include <algorithm>


class TreeNode
{
    public:
        bool endOfWord;
        std::array<std::shared_ptr<TreeNode>, 26> children;

        void isEndOfWord() { endOfWord = true; };
};

class WordTree
{
    std::size_t treeSize = int(0);
    public:
      std::array<std::shared_ptr<TreeNode>, 26> roots;
      std::array<char, 26> alphabet = {'a','b','c','d','e','f','g','h','i',
                                       'j','k','l','m','n','o','p','q','r',
                                       's','t','u','v','w','x','y','z'};
      void add(std::string word);
      bool find(std::string word);
      std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
      std::size_t size();

      char getLetter(std::uint8_t letterNum);
      int getFixedASCII(char letterNum);
      void sizeAddOne();

};

std::shared_ptr<WordTree> readDictionary(std::string filename);
bool nullNodeCheck(std::shared_ptr<TreeNode> currNode);
