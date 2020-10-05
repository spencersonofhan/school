#include "distributions.hpp"

// Returns a vector that records the numbers generated with uniform_int_distribution given the function parameters
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> uniformVector;
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_int_distribution<int> distI(min, max);

    // Make the DistributionPairs based off (max-min)/numberBins
    unsigned int binBoundaries = std::lround(static_cast<double>((max - min)) / numberBins);

    // Initialize the first bin and adds it to uniformVector
    DistributionPair bin0(min, (min + binBoundaries) - 1);
    uniformVector.push_back(bin0);

    // Fill uniformVector with DistributionPair objects with correct bins
    for (int i = 1; i < numberBins; i++)
    {
        DistributionPair dp(min + (i * binBoundaries), min + ((i * binBoundaries) + (binBoundaries - 1)));
        uniformVector.push_back(dp);
    }

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        auto genNum = distI(engine);
        auto genNumBin = std::floor(static_cast<double>(genNum - min) / binBoundaries);
        uniformVector[genNumBin].count++;
    }

    return uniformVector;
}

// Returns a vector that records the numbers generated with normal_distribution given the function parameters
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    std::vector<DistributionPair> normalVector;
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::normal_distribution<float> distFloat(mean, stdev);

    int minBin = mean - (4 * stdev);
    int maxBin = mean + (4 * stdev) - 1;
    int binBoundaries = std::round(static_cast<double>(maxBin - minBin) / numberBins);

    // Fill normalVector with DistributionPair objects with correct bins
    for (int i = 0; i < numberBins; i++)
    {
        DistributionPair dp(minBin + (i * binBoundaries), minBin + (i * binBoundaries) + (binBoundaries - 1));
        normalVector.push_back(dp);
    }

    // Generate random numbers and correctly bin them
    for (std::uint32_t i = 0; i < howMany; i++)
    {
        auto randNumber = distFloat(engine);
        int bin = std::floor((randNumber - minBin) / binBoundaries);

        if (randNumber < minBin)
        {
            normalVector[0].count++;
            continue;
        }
        else if (randNumber > maxBin)
        {
            normalVector[normalVector.size() - 1].count++;
            continue;
        }

        normalVector[bin].count++;
    }

    return normalVector;
}

// Returns a vector that records the numbers generated with poisson_distribution given the function parameters
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    std::vector<DistributionPair> poissonVector;
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::poisson_distribution<int> distInt(howOften);

    // Fill poissonVector with DistributionPair objects with correct bins
    for (int j = 0; j < numberBins; j++)
    {
        DistributionPair dp(j, j);
        poissonVector.push_back(dp);
    }

    // Generate random numbers and correctly bin them
    for (std::uint32_t i = 0; i < howMany; i++)
    {
        auto randNum = distInt(engine);
        poissonVector[randNum].count++;
    }

    return poissonVector;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    std::cout << title << std::endl;

    /*
    First get the max digit count from bins
    !code was inspired from these resources!
    - https://www.cprogramming.com/tutorial/iomanip.html
    - https://stackoverflow.com/questions/22648978/c-how-to-find-the-length-of-an-integer
    */
    auto mPLS = maxPlotLineSize;
    std::uint32_t minBinWidth = 0;
    std::uint32_t maxBinWidth = 0;
    std::uint32_t maxCount = 0;

    for (DistributionPair dp : distribution)
    {
        if (maxCount < dp.count)
        {
            maxCount = dp.count;
        }
        // Turns the dp.minValue into a string to find the amount of digits
        std::uint32_t length = std::to_string(dp.minValue).length();
        if (length > minBinWidth)
        {
            minBinWidth = length;
        }
        // Identical to above block except with maxValue
        if (length > maxBinWidth)
        {
            maxBinWidth = length;
        }
    }

    /*
    When plotting each DistributionPair, there will always be six characters that do not change from line to line. ( [,]<space>:<space> )
    I will subtract 6 (+1 too, I'm not entirely sure why but it does need it for proper output) + minBinWidth + maxBinWidth
    from the maxPlotLineSize copied variable (mPLS) to get the remaining amount of character space I can plot
    */
    mPLS -= (7 + minBinWidth + maxBinWidth);
    int starValue = maxCount / mPLS;
    char star = '*';

    // Formats and plots each DistributionPair object's count data
    for (std::uint32_t j = 0; j < distribution.size(); j++)
    {
        int numOfStars = distribution[j].count / starValue;
        std::cout << "[";
        std::cout << std::setw(minBinWidth) << std::right << distribution[j].minValue << ",";
        std::cout << std::setw(maxBinWidth) << std::right << distribution[j].maxValue << "] : ";
        std::cout << std::setw(maxPlotLineSize) << std::left << std::string(numOfStars, star) << "(" << numOfStars << ")" << std::endl;
    }
}
