#include "sortutils.hpp"

int main()
{
    std::cout << "Ayo this gon be on the test??" << std::endl;
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_int_distribution<int> randNum(-10000000, 10000000);
    SourceArray sArray;
    SourceArray sorted;
    SourceArray reversed;
    SourceArray organPipe;
    SourceArray rotated;

    // Make the source SourceArray
    for (decltype(sArray.max_size()) i = 0; i < sArray.max_size(); i++)
    {
        sArray[i] = randNum(engine);
    }

    sorted = sArray;
    std::sort(sorted.begin(), sorted.end());

    reversed = sorted;
    organPipe = sorted;
    rotated = sorted;

    std::reverse(std::begin(reversed), std::begin(reversed) + reversed.max_size());
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    // Organ pipe
    int orgPipMax = organPipe.max_size();
    int orgPipHalf = (orgPipMax / 2);
    for (decltype(organPipe.max_size()) i = (organPipe.max_size() / 2); i < organPipe.max_size(); i++)
    {
        organPipe[i] = organPipe[i - orgPipHalf];
    }

    for (auto i : organPipe)
    {
        std::cout << i << std::endl;
    }
    // I believe this to be correct but I have not tested it.



}
