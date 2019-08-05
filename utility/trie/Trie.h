#ifndef TRIE_H

#define TRIE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 * Trie structure that supports strings and ints as    *
 * keys to create a map to their corresponding data.   *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>

class Trie {

private:


    /*
     +++++ All potential single char ASCII(s) that may be used as keys +++++
     */

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';


    /*
     +++++ Node for creating paths to the data +++++
     */

    struct Node;


    /*
     +++++ Pointer to the begining of the Trie +++++
     */

    SharedPtr<Node> head;

    /*
     ++++ Returns unique key ++++
     */

    size_t hash(char letter) const;


    /*
     +++++ Returns the destination Node +++++
     */

    SharedPtr<Node> goTo(size_t indx) const;


    /*
     +++++ Returns the destination Node +++++
     */

    SharedPtr<Node> goTo(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const;


public:
   


    /*
     +++ Main C'tor +++
     */

    Trie();

    /*
     +++++ Stores data at the destination mapped with str. +++++
     */

    void push(const std::string &str, const SharedPtr<T> &data);

    /* 
     +++++ Stores data at the destination mapped with str, but params are forwarded to type T C'tor to create the data +++++
     */

    template<typename ... Params>

    void push(const std::string &str, Params&& ... params);


    /*
     +++++ Stores data at a destination that was mapped using index. +++++
     */

    void push(size_t indx, const SharedPtr<T> &data);

    /*
     +++++ Finds corresponding data of string in O(1) time complexity. Range of string is allowed ++++++                          
     */

    SharedPtr<T> map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const;

    /*
     +++++ Uses indx to map to destination and returns the data found there +++++
     */ 

    SharedPtr<T> map(size_t indx) const;

    /*
     +++++ Goes to destination and sets data to nullptr +++++
     */

    void eraseData(size_t indx);

    /*
     +++++ Goes to destination and sets data to nullptr +++++
     */

    void eraseData(const std::string &str);


    /*
     +++++ Finds the position of input string where mapping broke off. +++++
     +++++ ie:  Map In Trie -> "HELLO",  Input -> "HEL", Output -> 3   +++++
     */

    std::string::size_type getBreakPoint(const std::string &data, std::string::size_type start = 0) const;
    
}; // Trie


#endif