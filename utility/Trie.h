#ifndef TRIE_H

#define TRIE_H

template<typename T>

class Trie {

private:

    /*
     +++++++ All potential single char ASCII(s) that may be used as keys +++++++++++++
     */

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';

    /*
     ++++++ Node for creating paths to the symbols ++++++++
     */

    struct Node;

    Node *head;

    /*
     ++++ Returns unique key ++++
     */

    size_t hash(char letter) const;

public:

    /*
     +++ Main C'tor +++
    */ 

    Trie();

    /*
     +++++ Stores data at a destination that was mapped using str. +++++
     */

    void push(const std::string &str, T *data = nullptr);

    /*
     +++++ Stores data at a destination that was mapped using index. +++++
     */

    void push(size_t indx, T *data = nullptr);

    /*
     +++++++++ Finds corresponding symbol of string in O(1) time complexity.         ++++++++++
     +++++++++ Params: string containing data and the range (start and end) to read. ++++++++++
     +++++++++ Range is set to full string as defualt.                               ++++++++++
     */

    T *map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0);

    /*
     ++++++++++++ Gets the index of the string where mapping broke off.               +++++++++++++++++++
     ++++++++++++ Params: the string containing the key and the position of where to  +++++++++++++++++++
     ++++++++++++ start reading the string (set to begining of string as defualt).    +++++++++++++++++++
     */

    std::string::size_type getBreakPoint(const std::string &data, std::string::size_type start = 0);

    

}; // Trie


#endif