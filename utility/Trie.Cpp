
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

struct Trie::Node {

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

size_t Trie::hash(char letter) const {

    return letter - '!';
}




/*
 +++++ Returns the destination Node +++++
 */

SharedPtr<Node> Trie::goTo(size_t indx) const {

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

SharedPtr<Node> Trie::goTo(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const {
    
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

Trie::Trie()

    :head(nullptr)
{}





/*
 +++++ Stores data at the destination mapped with str. +++++
 */

void Trie::push(const std::string &str, const SharedPtr<T> &data) {

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
     ++++ Store data at destination. ++++
     */

    current->tPtr = data;

}





/*
 +++++ Stores data at a destination that was mapped using index. +++++
 */

void Trie::push(size_t indx, const SharedPtr<T> &data) {

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

SharedPtr<T> Trie::map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const {

    return goTo(data, start, end)->tPtr;

};




/*
 +++++ Uses indx to map to destination and returns the data found there +++++
 */ 

SharedPtr<T> Trie::map(size_t indx) const {

    
    return goTo(indx)->tPtr;

}

/*
 +++++ Goes to destination and sets data to nullptr +++++
 */

void Trie::eraseData(size_t indx) {
    goTo(indx)->tPtr = nullptr;
}



/*
 +++++ Goes to destination and sets data to nullptr +++++
 */

void Trie::eraseData(const std::string &str) {
    goTo(str)->tPtr = nullptr;
}




/*
 +++++ Finds the position of input string where mapping broke off. +++++
 +++++ ie:  Map In Trie -> "HELLO",  Input -> "HEL", Output -> 3   +++++
 */

std::string::size_type Trie::getBreakPoint(const std::string &data, std::string::size_type start = 0) const {

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