
#include <iostream>
#include "Trie.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 * Trie structure that supports strings and ints as    *
 * keys to create a map to their corresponding data.   *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 +++++ Node for creating paths to the data +++++
 */
template<typename T>
struct Trie<T>::Node {

    /*
     +++++ Ptr to T object. +++++
     */

    SharedPtr<T> tPtr;

    /*
     +++++ An array of Pointers to other Nodes +++++
     +++++ used to map to corresponding data . +++++
     */

    SharedPtr<Node> paths[NUM_OF_SINGLE_ASCII];

    /*
     +++++ Main C'Tor +++++
     */

    Node()
        :tPtr(nullptr)
    {}   

}; // Node





/*
 ++++ Returns unique key ++++
 */
template<typename T>
inline size_t Trie<T>::hash(char letter) const {

    return letter - '!';
}




/*
 +++++ Returns the destination Node +++++
 */
template<typename T>
SharedPtr<typename Trie<T>::Node> Trie<T>::goTo(size_t indx) const {

    /*
    +++++ If linked-list is empty +++++
    */

    if(!head) return nullptr;

    size_t modFactor = 10,
           denom     = 1,
           partOfIndx;


    SharedPtr<Node> current = head;

    /*
     +++++ Use each digit in indx to map to destination where result is located. ++++++
     */

    do {

        partOfIndx = indx % modFactor;

        size_t digit = partOfIndx/denom;

        if(!current->paths[digit]) return nullptr;

        current = current->paths[digit];

        modFactor *= 10;

        denom *= 10;
    }

    while(partOfIndx != indx);

    return current;
}





/*
 +++++ Returns the destination Node +++++
 */
template<typename T>
SharedPtr<typename Trie<T>::Node> Trie<T>::goTo(const std::string &data,  std::string::size_type start, std::string::size_type end) const {
    
    /*
    +++++ If linked-list is empty +++++
    */

    if(!head) return nullptr;

    /*
    ++++++ Default value of end ++++++
    */

    if(end == 0) end = data.size();

    SharedPtr<Node> current = head;

    /*
    +++++ Use string as key to map to destination where corresponding data lies +++++
    */

    while(start < end) {

        size_t indx = hash(data[start]);

        if(!current->paths[indx]) return nullptr;

        current = current->paths[indx];

        ++start;

    } 

    return current;
}




/*
 +++ Main C'tor +++
 */
template<typename T>
Trie<T>::Trie()

    :head(nullptr)
{}





/* 
 +++++ Stores data at the destination mapped with str. Params are forwarded to type T C'tor to create the data +++++
 */
template<typename T>
template<typename ... Params>
void Trie<T>::push(const std::string &str, Params&& ... params) {


   /*
    +++++ If linked-list is empty +++++
    */

    if(!head) head = SharedPtr<Node>(new Node);


    SharedPtr<Node> current = head;

    /* 
    ++++ Hash each letter and map to the destination where data will be stored ++++
    */

    for(char letter : str) {

        size_t indx = hash(letter);

        if(!current->paths[indx]) current->paths[indx] = SharedPtr<Node>(new Node);

        current = current->paths[indx];
    }

    /*
     +++++ Construct T object with params passed in and Create SharedPtr to T object. +++++
     */

    current->tPtr = SharedPtr<T>(new T(std::forward<Params>(params)...));

};


/*
 +++++ Stores data at a destination that was mapped using index. +++++
 */
template<typename T>
void Trie<T>::push(size_t indx, const SharedPtr<T> &data) {

    /*
    +++++ If linked-list is empty +++++
    */

    if(!head) head = SharedPtr<Node>(new Node);
    

    size_t modFactor = 10,
           denom     = 1,
           partOfIndx;

    SharedPtr<Node> current = head;

    /*
    +++++ Use each digit in indx to map to destination where result will be stored. +++++
    */

    do {

        partOfIndx = indx % modFactor;

        size_t digit = partOfIndx/denom;

        if(!current->paths[digit]) current->paths[digit] = SharedPtr<Node>(new Node);

        current = current->paths[digit];
        
        modFactor *= 10;

        denom  *= 10;
    }

    while( partOfIndx != indx);
    
    /*
    +++++ Store data at destination +++++
    */
    current->tPtr = data;
};





/*
 +++++ Finds corresponding data of string in O(1) time complexity. Range of string is allowed ++++++
 */
template<typename T>
inline SharedPtr<T> Trie<T>::map(const std::string &data,  std::string::size_type start, std::string::size_type end) const {

    /*
     +++++ Check if Node exist before dereferencing pointer +++++
     */ 
    if(SharedPtr<Node> nodePtr = goTo(data, start, end))
        /*
         +++++ Return pointer to T in Node +++++
         */
        return nodePtr->tPtr;

    return nullptr;

};




/*
 +++++ Uses indx to map to destination and returns the data found there +++++
 */ 
template<typename T>
inline SharedPtr<T> Trie<T>::map(size_t indx) const {

    /*
     +++++ Check if Node exist before dereferencing pointer +++++
     */ 
    if(SharedPtr<Node> nodePtr = goTo(indx))
        /*
         +++++ Return pointer to T in Node +++++
         */
        return nodePtr->tPtr;

    return nullptr;

}

/*
 +++++ Goes to destination and sets data to nullptr +++++
 */
template<typename T>
inline void Trie<T>::eraseData(size_t indx) {
    goTo(indx)->tPtr = nullptr;
}



/*
 +++++ Goes to destination and sets data to nullptr +++++
 */
template<typename T>
inline void Trie<T>::eraseData(const std::string &str) {
    goTo(str)->tPtr = nullptr;
}




/*
 +++++ Finds the position of input string where mapping broke off. +++++
 +++++ ie:  Map In Trie -> "HELLO",  Input -> "HEL", Output -> 3   +++++
 */
template<typename T>
std::string::size_type Trie<T>::getBreakPoint(const std::string &data, std::string::size_type start) const {

    /*
     +++++ If linked-list is empty +++++
     */

    if(!head) return start;

    SharedPtr<Node> current = head;

    /*
     +++++++ Map as much as possible +++++++
     */

    for(decltype(start) len = data.size(); start < len; ++start) {
        
        size_t indx = hash(data[start]);

        if(!current->paths[indx]) break;

        current = current->paths[indx];
    }

    /*
     +++++ Break point +++++++
     */

    return start;
}