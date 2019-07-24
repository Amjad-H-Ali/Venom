#ifndef TRIE_H

#define TRIE_H

template<typename T>

class Trie {

private:

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';

    struct Node;

    Node *head;

    size_t hash(const char letter) const;

public:

    Trie();


    void push(const char *str, T *type);

    /*
        *
        * Finds corresponding Ptr_t data of string in O(1) time complexity.
        * Params: string containing data and the range (start and end) to read.
        * Range is set to full string as defualt.
    */
    T *map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0);

    /*
        *
        * Gets the index of the string of where the data stopped matching.
        * Params: the string containing the data and the position of where to 
        * start reading the string (set to begining of string as defualt).
        *
    */
    std::string::size_type getBreakPoint(const std::string &data, std::string::size_type start = 0);

    

}; // Trie


#endif