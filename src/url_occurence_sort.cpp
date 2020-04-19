#include <unistd.h>
#include "url_occurence_sort.h"
#include "glog/logging.h"
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <iterator>
#include <algorithm>

urlOccurenceSort::urlOccurenceSort(std::string inputFilePath, std::string tempFilePrefix)
{
    mInputFilePath = inputFilePath;
    mTempFilePrefix = tempFilePrefix;
}

urlOccurenceSort::~urlOccurenceSort()
{
    int rtn =0;
    for(auto it: mTempFiles)
    {
        std::string realFilePath = mTempFilePrefix + "/" + it;
        rtn = remove(realFilePath.c_str());
        if (rtn != 0)
        {
            LOG(ERROR) << "remove temp file failed, file path is " << realFilePath;
        }
    }
}

int urlOccurenceSort::solve(std::vector<std::pair<std::string, int>>& answer)
{
    answer.clear();

    // check input file exist
    int rtn = fileExist(mInputFilePath);
    if (rtn != 0)
    {
        LOG(ERROR) << "input file " << mInputFilePath << " not exist!";
        return -1;
    }

    // begin read input file
    std::ifstream inputStream(mInputFilePath);
    if (!inputStream.is_open())
    {
        LOG(ERROR) << "open file " << mInputFilePath << " failed!";
        return -2;
    }
    while (inputStream.good())
    {
        std::string url = "";
        getline(inputStream, url);
        if (url.empty())
            continue;
        // hash the url and append it to correspond block splitly
        int hashCode = hash(url);
        mTempFiles.insert(std::to_string(hashCode));
        std::string realFilePath = mTempFilePrefix + "/" + std::to_string(hashCode);
        std::ofstream outputStream;
        outputStream.open(realFilePath, std::ios::out | std::ios::app);
        if (!outputStream.good())
        {
            LOG(ERROR) << "open temp outputfile failed, file is " << realFilePath;
            return -3;
        }
        outputStream << url << std::endl;
    }
    if (!inputStream.eof())
    {
        LOG(ERROR) << "read file from inputfilestream failed , file is " << mInputFilePath;
        return -3;
    }
    inputStream.close();

    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> answerQueue;

    // read from temp file and comput result
    for (auto tempFile: mTempFiles)
    {
        std::string realFilePath = mTempFilePrefix + "/" + tempFile;
        std::ifstream inputStream(realFilePath);
        if (!inputStream.is_open())
        {
            LOG(ERROR) << "open file " << realFilePath << " failed!";
            return -2;
        }
        std::unordered_map<std::string, int> url2Times; 
        while (inputStream.good())
        {
            std::string url = "";
            getline(inputStream, url);
            if (url.empty())
            continue;
            url2Times[url]++;
        }
        if (!inputStream.eof())
        {
            LOG(ERROR) << "read file from inputfilestream failed , file is " << realFilePath;
            return -4;
        }
        for (auto it: url2Times)
        {
            std::string url = it.first;
            int times = it.second;
            std::pair<int, std::string> singleResult = make_pair(times, url);
            if (answerQueue.size() < 100)
            {
                answerQueue.push(singleResult);
            }
            else if (singleResult > answerQueue.top())
            {
                answerQueue.pop();
                answerQueue.push(singleResult);
            }
        }
    }
    while (!answerQueue.empty())
    {
        auto singleResult = answerQueue.top();
        answerQueue.pop();
        answer.push_back(make_pair(singleResult.second, singleResult.first));
    }
    std::reverse(answer.begin(), answer.end());
    // for (auto it: answer)
    // {
    //     LOG(INFO) << "url " << it.first << " occur " << it.second << " times";
    // }
    return 0;
}

int urlOccurenceSort::hash(std::string url)
{
    const long long int mod = 19660813;
    long long int ret = 0;
    for (int i=0; i < url.length(); i++)
    {
        long long int ch = url[i];
        ret = (ret * 3 + ch) % mod;
    }
    return int(ret);
}

int urlOccurenceSort::fileExist(std::string fileName)
{
    return access(fileName.c_str(), 0);
}