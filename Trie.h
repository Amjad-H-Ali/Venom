#ifndef TRIE_H

#define TRIE_H

class Trie {

private:

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';

    struct Node {
        
        bool val;

        Node *paths[NUM_OF_SINGLE_ASCII];

        Node()
            :val(false), paths{nullptr}
        {};
    };

    Node *head;

public:

    Trie()
        :head(nullptr)
    {};

    

}; // Trie


#endif