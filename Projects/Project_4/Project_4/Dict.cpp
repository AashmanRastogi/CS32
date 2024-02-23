//
//  Dict.cpp
//  Project_4
//
//  Created by Aashman Rastogi on 8/7/23.
//

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>
#include <unordered_map>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

class DictionaryImpl
{
public:
    DictionaryImpl(int maxbuckets)
    {
        m_words.resize(maxbuckets);
    }

    void insert(string word);
    void lookup(string letters, void callback(string)) const;

private:
    vector<list<string>> m_words;
    size_t hashfunc(const string& word) const;
};

size_t DictionaryImpl::hashfunc(const string& word) const
{
    unordered_map<char, int> charCount;
    for (char c : word) {
        charCount[c]++;
    }

    size_t hashValue = 0;
    for (char c : word) {
        hashValue = hashValue * 31 + charCount[c];
    }

    size_t bucketNum = hashValue % m_words.size();
    return bucketNum;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if (!word.empty())
    {
        size_t bucketNum = hashfunc(word);

        list<string>& wordList = m_words[bucketNum];
        wordList.push_back(word);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const {
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    size_t bucketNum = hashfunc(letters);

    const list<string>& wordList = m_words[bucketNum];

    unordered_map<char, int> lettersCount;
    for (char c : letters) {
        lettersCount[c]++;
    }

    for (const string& word : wordList) {
        unordered_map<char, int> wordCount;
        for (char c : word) {
            wordCount[c]++;
        }

        bool isAnagram = true;
        for (auto it = lettersCount.begin(); it != lettersCount.end(); ++it) {
            if (wordCount[it->first] != it->second) {
                isAnagram = false;
                break;
            }
        }

        if (isAnagram) {
            callback(word);
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}


void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
