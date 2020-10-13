#include "sortutils.hpp"

void printOutTimes(std::string, std::array<std::chrono::milliseconds, 5>);
std::chrono::milliseconds copyAndSort(const SourceArray&);

void initializeRawArrayFromStdArray(const std::array<int, HOW_MANY_ELEMENTS>& source, int dest[])
{
    for(std::uint32_t i = 0; i < source.max_size(); i++)
    {
        dest[i] = source[i];
    }
}

// Organ pipe (Copy first half to second then reverse the second half)
void organPipeStdArray(std::array<int, HOW_MANY_ELEMENTS>& data)
{
    int orgPipMax = data.max_size();
    int orgPipHalf = (orgPipMax / 2);

    for (std::uint32_t i = orgPipHalf; i < orgPipMax; i++)
    {
        data[i] = data[i - orgPipHalf];
    }
    std::reverse(std::begin(data) + orgPipHalf, std::begin(data) + orgPipMax);
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Arrays to hold the SourceArray parameters and the total sort time for each array type
    std::array<std::chrono::milliseconds, 5> totalTimeArray;

    totalTimeArray[0] = copyAndSort(random);
    totalTimeArray[1] = copyAndSort(sorted);
    totalTimeArray[2] = copyAndSort(reversed);
    totalTimeArray[3] = copyAndSort(organPipe);
    totalTimeArray[4] = copyAndSort(rotated);
    printOutTimes("Raw Array", totalTimeArray);
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{

}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{

}

void printOutTimes(std::string name, std::array<std::chrono::milliseconds, 5> data)
{
    std::cout << " --- " << name << " Performance ---" << std::endl;
    for (uint32_t i = 0; i < data.max_size(); i++)
    {
        std::cout << std::setw(PRINTOUT_WIDTH) << std::left << PRE_SORT_NAMES[i]
        << " : " << data[i].count() << " ms\n" << std::endl;
    }
}

std::chrono::milliseconds copyAndSort(const SourceArray& arrayCopy)
{
    std::chrono::milliseconds totalTime(0);
    std::cout << totalTime.count() << std::endl;
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
