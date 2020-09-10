#include "SortResults.h"
#include "Calibration.h"
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

//Used for sort algorithm
bool sortResults(Result a, Result b)
{
    return (a.time < b.time);
}

//Sorts the sim results into order of completion time and then extracts the results for each sim of which calibration crossed the finish first
Result SingleBestResult(std::vector<Result> simResults)
{
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
    Result best = simResults[i];
    return best;
}


//Organises the best results
std::string Winner(std::vector<Result> &bestList)
{
    //@TODO - Make this function actually get the best overall result rather than displaying result 1 all the time
    //@LAST BIT BEFORE SUBMIT
    std::string best = bestList[1].calFile;
    return best;
}