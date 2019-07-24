

struct Trie::Node {

    T *type;

    Node *paths[NUM_OF_SINGLE_ASCII];

    Node()
        :T(nullptr), paths{nullptr}
    {}

}; // Node



size_t Trie::hash(const char letter) const {

    return letter - '!';
}



Trie::Trie()
    :head(nullptr)
{}


void Trie::push(const char *str, T *type) {
   
    Node *current = head;

    for(size_t c = 0; str[c]; ++c) {

        size_t indx = hash(str[c]);

        if(!current->paths[indx]) current->paths[indx] = new Node;

        current = current->paths[indx];
    }


    current->type = type;

}

/*
    *
    * Finds corresponding Ptr_t data of string in O(1) time complexity.
    * Params: string containing data and the range (start and end) to read.
    * Range is set to full string as defualt.
*/
T *Trie::map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) {

    if(end == 0) end = data.size();

    Node *current = head;

    while(start < end) {

        size_t indx = hash(data[start]);

        if(!current->paths[indx]) return nullptr;

        ++start;

        current = current->paths[indx];

    } 

    return current->type;

};


/*
    *
    * Gets the index of the string of where the data stopped matching.
    * Params: the string containing the data and the position of where to 
    * start reading the string (set to begining of string as defualt).
    *
*/
std::string::size_type Trie::getBreakPoint(const std::string &data, std::string::size_type start = 0) {

    Node *current = head;

    for(decltype(start) len = data.size(); start < len; ++start) {
        
        size_t indx = hash(data[start]);

        if(!current->paths[indx]) break;

        current = current->paths[indx];
    }

    return start;
}
