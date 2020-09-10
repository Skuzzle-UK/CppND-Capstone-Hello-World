#ifndef SORTRESULT_H_
#define SORTRESULT_H_

#include <vector>
#include <string>
#include <memory>
#include "Result.h"

bool sortResults(Result a, Result b);

Result SingleBestResult(std::vector<Result> simResults);

std::string Winner(std::vector<Result> &bestList);

#endif /* SORTRESULT_H_ */