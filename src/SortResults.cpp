#include "SortResults.h"
#include "Calibration.h"
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

bool sortResults(Result a, Result b)
{
    return (a.time < b.time);
}

Result SingleBestResult(std::vector<Result> &simResults)
{
    Result best;

    //@TODO write function to find best result by simResult.time - Drop times of 0
    //Just return best result from vector.
    std::sort (simResults.begin(), simResults.end(), sortResults);
    int i = 0;
    while (simResults[i].time <= 0 && i < simResults.size() - 1)
    {
        i++;
    }
    if (simResults[i].time <= 0)
    {
        simResults[i].calFile = "../none - ALL FAILED";
    }
    best = simResults[i];
    return best;
}


//Organises the best results
std::string Winner(std::vector<Result> &bestList)
{
    std::string best = bestList[1].calFile;
    return best;
}