
/*
 ++++++ Node for creating paths to the symbols ++++++++
 */

struct Trie::Node {

    T *type;

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
 ++++++++ Adds symbol to Trie      ++++++++
 ++++++++ Uses str literal as map  ++++++++
 */

void Trie::push(const char *str, T *symbol) {
   
    Node *current = head;

    /* 
     ++++ Hash each letter to map symbol ++++
     */

    for(size_t c = 0; str[c]; ++c) {

        size_t indx = hash(str[c]);

        if(!current->paths[indx]) current->paths[indx] = new Node;

        current = current->paths[indx];
    }

    /*
     ++++ Add symbol to mapped place in Trie. ++++
     */

    current->symbol = symbol;

}

/*
 +++++++++ Finds corresponding symbol of string in O(1) time complexity.         ++++++++++
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
     ++++++++ Use string data as key to map to corresponding symbol +++++++++
     */

    while(start < end) {

        size_t indx = hash(data[start]);

        if(!current->paths[indx]) return nullptr;

        ++start;

        current = current->paths[indx];

    } 

    return current->symbol;

};


/*
 ++++++++++++ Gets the index of the string of where it stopped mapping.           +++++++++++++++++++
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
