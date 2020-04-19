#ifndef url_occurence_sort_h
#define url_occurence_sort_h
#include <iostream>
#include <set>
#include <fstream>
#include <map>
#include <vector>

class urlOccurenceSort{
public:
    //user shoulde confirm the tempFilePrefix directory already exist and is empty
    urlOccurenceSort(std::string inputFilePath, std::string tempFilePrefix = ".temp");
    ~urlOccurenceSort();
    // return 0 if success, the result is save to answer
    // answer sample {{"www.baidu.com", 100}, {"www.google.com", 99}}
    int solve(std::vector<std::pair<std::string, int>>& answer);
    int hash(std::string url);
private:
    std::string mInputFilePath, mTempFilePrefix;
    
    /*
    mTempFilePrefix
    ├── mTempFiles[0]
    └── mTempFiles[1]
    */
    std::set<std::string> mTempFiles;

    int fileExist(std::string fileName);
};

#endif