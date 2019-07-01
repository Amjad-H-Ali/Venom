#ifndef TRIE_H

#define TRIE_H

template<typename T>

class Trie {

private:

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';

    struct Node {

        T type;

        /*
            *
            * Used to determine if data member "type" exist when T is of Symbol type.
            * Symbol is an enum and enums are default initialized to 0, which is always false.
            *
        */
        bool exists;

        Node *paths[NUM_OF_SINGLE_ASCII];

        Node()
            :exists(false), paths{nullptr}
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


    void push(const char *str, T type) {
       
        Node *current = head;

        for(size_t c = 0; str[c]; ++c) {

            size_t indx = hash(str[c]);

            if(!current->paths[indx]) current->paths[indx] = new Node;

            current = current->paths[indx];
        }

        current->exists = true;

        current->type = type;


    }

    

}; // Trie


#endif