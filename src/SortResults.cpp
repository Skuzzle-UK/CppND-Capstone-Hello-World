#include "SortResults.h"

Result BestResult(std::vector<Result> &simResults)
{
    Result best;

    //@TODO write function to find best result by simResult.time - Drop times of 0
    //Just return best result from vector.
    for(int i = 0; i < simResults.size(); i++)
    {
        if (simResults[i].time != 0)
        {
            if (best.time > 0)
            {
                if (simResults[i].time < best.time)
                {
                    best = simResults[i];
                }
            }
            else
            {
                best = simResults[i];
            }
        }
    }

    return best;
}