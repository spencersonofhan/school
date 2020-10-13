#include "sortutils.hpp"

int main()
{
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_int_distribution<int> randNum(-10000000, 10000000);
    SourceArray random;
    SourceArray sorted;
    SourceArray reversed;
    SourceArray organPipe;
    SourceArray rotated;

    // Make the source SourceArray
    for (decltype(random.max_size()) i = 0; i < random.max_size(); i++)
    {
        random[i] = randNum(engine);
    }

    // Create the sorted array so it can be used and copied
    sorted = random;
    std::sort(sorted.begin(), sorted.end());

    reversed = sorted;
    rotated = sorted;
    organPipe = sorted;

    std::reverse(std::begin(reversed), std::begin(reversed) + reversed.max_size());
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
    organPipeStdArray(organPipe);

    evaluateRawArray(random, sorted, reversed, organPipe, rotated);
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);
}
