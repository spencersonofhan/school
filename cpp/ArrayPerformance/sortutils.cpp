#include "sortutils.hpp"

void printOutTimes(std::string, std::array<std::chrono::milliseconds, 5>);
std::chrono::milliseconds copyAndSort(const SourceArray&);
std::chrono::milliseconds copyAndSortRaw(const SourceArray&);

// Simple copy to raw array from std::array by iteration
void initializeRawArrayFromStdArray(const std::array<int, HOW_MANY_ELEMENTS>& source, int dest[])
{
    for (std::uint32_t i = 0; i < source.max_size(); i++)
    {
        dest[i] = source[i];
    }
}

// Organ pipe (Copy first half to second then reverse the second half)
void organPipeStdArray(std::array<int, HOW_MANY_ELEMENTS>& data)
{
    auto orgPipMax = data.max_size();
    auto orgPipHalf = (orgPipMax / 2);

    for (decltype(orgPipMax) i = orgPipHalf; i < orgPipMax; i++)
    {
        data[i] = data[i - orgPipHalf];
    }
    std::reverse(std::begin(data) + orgPipHalf, std::begin(data) + orgPipMax);
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // totalTimeArray will hold each type of arrays' sort times.
    std::array<std::chrono::milliseconds, 5> totalTimeArray;

    totalTimeArray[0] = copyAndSortRaw(random);
    totalTimeArray[1] = copyAndSortRaw(sorted);
    totalTimeArray[2] = copyAndSortRaw(reversed);
    totalTimeArray[3] = copyAndSortRaw(organPipe);
    totalTimeArray[4] = copyAndSortRaw(rotated);
    printOutTimes("Raw Array", totalTimeArray);
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // totalTimeArray will hold each type of arrays' sort times.
    std::array<std::chrono::milliseconds, 5> totalTimeArray;

    totalTimeArray[0] = copyAndSort(random);
    totalTimeArray[1] = copyAndSort(sorted);
    totalTimeArray[2] = copyAndSort(reversed);
    totalTimeArray[3] = copyAndSort(organPipe);
    totalTimeArray[4] = copyAndSort(rotated);
    printOutTimes("std::array", totalTimeArray);
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // totalTimeArray will hold each type of arrays' sort times.
    std::array<std::chrono::milliseconds, 5> totalTimeArray;

    totalTimeArray[0] = copyAndSort(random);
    totalTimeArray[1] = copyAndSort(sorted);
    totalTimeArray[2] = copyAndSort(reversed);
    totalTimeArray[3] = copyAndSort(organPipe);
    totalTimeArray[4] = copyAndSort(rotated);
    printOutTimes("std::vector", totalTimeArray);
}

// Prints out the totatTimeArray in accordance with the sample output on the assignments' Canvas page
void printOutTimes(std::string name, std::array<std::chrono::milliseconds, 5> totalTimeArray)
{
    std::cout << "\n --- " << name << " Performance ---" << std::endl;
    for (uint32_t i = 0; i < totalTimeArray.max_size(); i++)
    {
        std::cout << std::setw(PRINTOUT_WIDTH) << std::left << PRE_SORT_NAMES[i]
                  << " : " << totalTimeArray[i].count() << " ms" << std::endl;
    }
}

// Helper function that copies and sorts the arrayCopy HOW_MANY_TIMES times
std::chrono::milliseconds copyAndSort(const SourceArray& arrayCopy)
{
    std::chrono::milliseconds totalTime(0);
    for (std::uint32_t j = 0; j < HOW_MANY_TIMES; j++)
    {
        std::array<int, HOW_MANY_ELEMENTS> theCopy = arrayCopy;

        auto startTime = std::chrono::steady_clock::now();
        std::sort(std::begin(theCopy), std::end(theCopy));
        auto endTime = std::chrono::steady_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    }
    return totalTime;
}

// Accomplishes the same goal as copyAndSort but with primitive arrays
std::chrono::milliseconds copyAndSortRaw(const SourceArray& arrayCopy)
{
    std::chrono::milliseconds totalTime(0);
    for (std::uint32_t j = 0; j < HOW_MANY_TIMES; j++)
    {
        int raw[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(arrayCopy, raw);

        auto startTime = std::chrono::steady_clock::now();
        std::sort(raw, raw + HOW_MANY_ELEMENTS);
        auto endTime = std::chrono::steady_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    }
    return totalTime;
}
