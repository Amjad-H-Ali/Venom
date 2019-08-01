
/*
 ++++++ Node for creating paths to the symbols ++++++++
 */

struct Trie::Node {

    T *tPtr;

    Node *paths[NUM_OF_SINGLE_ASCII];

    Node()
        :T(nullptr), paths{nullptr}
    {}

}; // Node


/*
 ++++ Returns unique key ++++
 */

size_t Trie::hash(char letter) const {

    return letter - '!';
}


/*
 +++ Main C'tor +++
*/

Trie::Trie()

    :head(nullptr)
{}

/*
 +++++ Stores data at a destination that was mapped using str. +++++
 */

void Trie::push(const std::string &str, T *data) {

    /*
     +++++ If linked-list is empty +++++
     */

    if(!head) head = new Node;

    Node *current = head;

    /* 
     ++++ Hash each letter to map data ++++
     */

    for(char letter : str) {

        size_t indx = hash(letter);

        if(!current->paths[indx]) current->paths[indx] = new Node;

        current = current->paths[indx];
    }

    /*
     ++++ Add data to mapped place in Trie. ++++
     */

    current->tPtr = data;

}

/*
 +++++ Stores data at a destination that was mapped using index. +++++
 */

void Trie::push(size_t indx, T *data) {

    /*
     +++++ If linked-list is empty +++++
     */

    if(!head) head = new Node;

    size_t modFactor = 10,
           denom     = 1,
           partOfIndx;

    Node *current = head;

    /*
     +++++ Use each digit in indx to map to destination where result will be stored. ++++++
     */

    do {

        partOfIndx = indx % modFactor;

        size_t digit = partOfIndx/denom;

        if(!current->paths[digit]) current->paths[digit] = new Node;

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
 +++++++++ Finds corresponding data of string in O(1) time complexity.           ++++++++++
 +++++++++ Params: string containing data and the range (start and end) to read. ++++++++++
 +++++++++ Range is set to full string as defualt.                               ++++++++++
 */

T *Trie::map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) {

    /*
     ++++++ Default value of end ++++++
     */

    if(end == 0) end = data.size();

    Node *current = head;

    /*
     ++++++++ Use string data as key to map to corresponding data +++++++++
     */

    while(start < end) {

        size_t indx = hash(data[start]);

        if(!current->paths[indx]) return nullptr;

        current = current->paths[indx];

        ++start;

    } 

    return current->tPtr;

};

/*
 +++++ Uses indx to map to destination and returns the data found there +++++
 */ 

T *Trie::map(size_t indx) {

    size_t modFactor = 10,
           denom     = 1,
           partOfIndx;

    Node *current = head;

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
    
    
    return current->tptr;

}


/*
 ++++++++++++ Gets the index of the string where mapping broke off.               +++++++++++++++++++
 ++++++++++++ Params: the string containing the key and the position of where to  +++++++++++++++++++
 ++++++++++++ start reading the string (set to begining of string as defualt).    +++++++++++++++++++
 */

std::string::size_type Trie::getBreakPoint(const std::string &data, std::string::size_type start = 0) {

    Node *current = head;

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
