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
     +++++ Adds symbol to Trie. Uses string as map to destination. Second param, the data +++++++
     +++++ that will be stored at destination, is nullptr by default.                     +++++++
     */
    
    void push(const std::string &str, T *symbol = nullptr);

    /*
     +++++++++ Finds corresponding symbol of string in O(1) time complexity.         ++++++++++
     +++++++++ Params: string containing data and the range (start and end) to read. ++++++++++
     +++++++++ Range is set to full string as defualt.                               ++++++++++
     */

    T *map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0);

    /*
     ++++++++++++ Gets the index of the string of where it stopped mapping.           +++++++++++++++++++
     ++++++++++++ Params: the string containing the key and the position of where to  +++++++++++++++++++
     ++++++++++++ start reading the string (set to begining of string as defualt).    +++++++++++++++++++
     */

    std::string::size_type getBreakPoint(const std::string &data, std::string::size_type start = 0);

    

}; // Trie


#endif