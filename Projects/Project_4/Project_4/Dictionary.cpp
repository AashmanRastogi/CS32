//#include "Dictionary.h"
//#include <iostream>
//#include <string>
//#include <functional>
//#include <list>
//#include <vector>
//#include <algorithm>
//#include <cctype>
//#include <utility>  // for swap
//using namespace std;
//
//void removeNonLetters(string& s);
//void generateNextPermutation(string& permutation);
//
//  // This class does the real work of the implementation.
//
//class DictionaryImpl
//{
//  public:
//    DictionaryImpl(int maxbuckets)
//    {
//        for (int i = 0; i <maxbuckets; i++)
//        {
//            list<string>* new_list = new list<string>;
//            m_words.push_back(new_list);
//        }
//    }
//
//    ~DictionaryImpl()
//    {
//        for (int i = 0; i < m_words.size(); i++)
//        {
//            delete m_words[i];
//        }
//    }
//
//    void insert(string word);
//    void lookup(string letters, void callback(string)) const;
//  private:
//    vector<list<string>*> m_words;
//    size_t hashfunc(const string& word) const;
//};
//
//
//// framework that i might follow for insertion
///*
//
//get words store in a separatte variable and sort.
//then gets its hash value and and store at respectiev index in the vector
//if hash value already exists for another word push_back adds it to the end of the list that originates from it
// if not it creates a new bucket at the index and starts a new list from it
//*/
//
//size_t DictionaryImpl::hashfunc(const string& word) const
//{
//    hash<string> strhash;                                 //hash function that uses <functional>
//    string sorted_word = word;
//    sort(sorted_word.begin(),sorted_word.end());
//    size_t hashValue = strhash(sorted_word);              //compute hash functions's number
//    size_t bucketNum = hashValue % m_words.size();        //convert to our own number
//    return bucketNum;
//}
//
//void DictionaryImpl::insert(string word)
//{
//    removeNonLetters(word);
//    if (!word.empty())
//    {
//        string sorted_word = word;
//        sort(sorted_word.begin(),sorted_word.end());
//        size_t bucketNum = hashfunc(sorted_word);        //use hash function to compute bucket number
//
//        list<string>* ptr = m_words[bucketNum];
//        ptr->push_back(word);
//    }
//}
//
//void DictionaryImpl::lookup(string letters, void callback(string)) const {
//    if (callback == nullptr)
//        return;
//
//    removeNonLetters(letters);
//    if (letters.empty())
//        return;
//
//    string sorted_letters = letters;
//    sort(sorted_letters.begin(), sorted_letters.end());
//
//    size_t bucketNum = hashfunc(sorted_letters); // Use hash function to compute bucket number
//
//    list<string>* wordList = m_words[bucketNum]; // Get the list at the bucket
//
//    for (const string& word : *wordList) { // Iterate over the list
//        string sorted_word = word;
//        sort(sorted_word.begin(), sorted_word.end());
//
//        if (sorted_word == sorted_letters) {
//            callback(word);
//        }
//    }
//}
//
//void removeNonLetters(string& s)
//{
//    string::iterator to = s.begin();
//    for (string::const_iterator from = s.begin(); from != s.end(); from++)
//    {
//        if (isalpha(*from))
//        {
//            *to = tolower(*from);
//            to++;
//        }
//    }
//    s.erase(to, s.end());  // chop everything off from "to" to end.
//}
//
//  // Each successive call to this function generates the next permutation of the
//  // characters in the parameter.  For example,
//  //    string s = "eel";
//  //    generateNextPermutation(s);  // now s == "ele"
//  //    generateNextPermutation(s);  // now s == "lee"
//  //    generateNextPermutation(s);  // now s == "eel"
//  // You don't have to understand this function's implementation.
//void generateNextPermutation(string& permutation)
//{
//    string::iterator last = permutation.end() - 1;
//    string::iterator p;
//
//    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
//        ;
//    if (p != permutation.begin())
//    {
//        string::iterator q;
//        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
//            ;
//        swap(*(p-1), *(q-1));
//    }
//    for ( ; p < last; p++, last--)
//        swap(*p, *last);
//}
//
////******************** Dictionary functions ******************************
//
//// These functions simply delegate to DictionaryImpl's functions
//// You probably don't want to change any of this code
//
//Dictionary::Dictionary(int maxBuckets)
//{
//    m_impl = new DictionaryImpl(maxBuckets);
//}
//
//Dictionary::~Dictionary()  // need to change this too
//{
//    delete m_impl;
//}
//
//void Dictionary::insert(string word)
//{
//    m_impl->insert(word);
//}
//
//void Dictionary::lookup(string letters, void callback(string)) const
//{
//    m_impl->lookup(letters,callback);
//}
