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


//Organises the best results to find the winning calibration
std::string Winner(std::vector<Result> &bestList)
{
    //Puts calibration files into unordered_map to count up the number of each calibration in the bestList
    std::unordered_map<std::string, int> winner;
    for (int i = 0; i < bestList.size(); i++)
    {
        if (winner.find(bestList[i].calFile) == winner.end())
        {
            winner[bestList[i].calFile] = 1;
        }
        else
        {
            winner[bestList[i].calFile]++;
        }
        
    }

    //Look through unordered_map to find key item which holds the largest value (the winner)
    std::string best;
    int bestMapSoFarCount = 0; //just keeps count
    for (auto x : winner)
    {
        if (x.second > bestMapSoFarCount)
        {
            best = x.first;
            bestMapSoFarCount++;
        }
    }

    return best;
}