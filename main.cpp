#include <iostream>

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

#include <algorithm>

class WordText
{
    private:
        std::unordered_map<std::string, std::vector<size_t>> wordMap;

    public:
        WordText(const std::string& text);
        ~WordText() {}
        std::pair<size_t, size_t> getPair(const std::string& word1, const std::string& word2);
};

WordText::WordText(const std::string& text)
{
    std::istringstream ss(text);

    size_t iter = 0;

    std::string word;

    while(ss >> word)
    {
        word.erase(std::remove_if(word.begin(), word.end(),
        []( auto const& c ) -> bool { return !std::isalnum(c); } ), word.end());

        wordMap[word].push_back(iter);
        ++iter;
    }
}

std::pair<size_t, size_t> WordText::getPair(const std::string& word1, const std::string& word2)
{
    if(wordMap.find(word1) == wordMap.end() ||
       wordMap.find(word2) == wordMap.end()) return {0, 0};

    std::vector<size_t> indexes1 = wordMap[word1];
    std::vector<size_t> indexes2 = wordMap[word2];

    size_t iter1 = 0;
    size_t iter2 = 0;

    std::pair<size_t, size_t> curMinPiar = {0, 0};

    int minLen = INT_MAX;

    while(iter1 < indexes1.size() && iter2 < indexes2.size())
    {

        int curLen = abs(indexes1[iter1] - indexes2[iter2]);

        if(curLen < minLen) {
            curMinPiar = {std::min(indexes1[iter1], indexes2[iter2]),
                          std::max(indexes1[iter1], indexes2[iter2])};

            minLen = curLen;
        }

        if(indexes1[iter1] < indexes2[iter2])
            ++iter1;

        else if(indexes1[iter1] > indexes2[iter2])
            ++iter2;
    }
    return curMinPiar;
}

int main()
{
    WordText wt("hello World of World Geeks, there something World!");
    auto res = wt.getPair("something", "World");
    std::cout << "res = " << res.first << ' ' << res.second << '\n';
    return 0;
}

