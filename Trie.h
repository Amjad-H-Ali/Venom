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
        {}
    };

    Node *head;

    size_t hash(const char letter) const {
        
        return letter - '!';
    }

public:

    Trie()
        :head(nullptr)
    {}


    void push(const char *str) {
       
        Node *current = head;

        for(size_t c = 0; str[c]; ++c) {

            size_t indx = hash(str[c]);

            if(!current->paths[indx]) current->paths[indx] = new Node;

            current = current->paths[indx];
        }


    }

    

}; // Trie


#endif