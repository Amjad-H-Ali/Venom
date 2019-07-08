#ifndef TRIE_H

#define TRIE_H

template<typename Ptr_t>

class Trie {

private:

    static constexpr size_t NUM_OF_SINGLE_ASCII = '~' - '!';

    struct Node {

        Ptr_t type;

        Node *paths[NUM_OF_SINGLE_ASCII];

        Node()
            :Ptr_t(nullptr), paths{nullptr}
        {}

    }; // Node


    Node *head;

    size_t hash(const char letter) const {

        return letter - '!';
    }

public:

    Trie()
        :head(nullptr)
    {}


    void push(const char *str, Ptr_t type) {
       
        Node *current = head;

        for(size_t c = 0; str[c]; ++c) {

            size_t indx = hash(str[c]);

            if(!current->paths[indx]) current->paths[indx] = new Node;

            current = current->paths[indx];
        }


        current->type = type;

    }


    Ptr_t map(const char *str) {

        if(!str) return nullptr;
        
        Node *current = head;

        for(size_t c = 0; str[c]; ++c) {

            size_t indx = hash(str[c]);

            if(!current->paths[indx]) return nullptr;

            current = current->paths[indx]; 
        }

        return current->type;

    };


    /*
        *
        * Gets the index of the string of where the data stopped matching.
        * Params: the string containing the text from the input file &
        * the position of where to start reading from the string.
        *
    */
    std::string::size_type getBreakPoint(const std::string &data, decltype(data.size()) start) {
    
        Node *current = head;

        for(decltype(data.size()) len = data.size(); start < len; ++start)
            
            size_t indx = hash(data[start]);

            if(!current->paths[indx]) break;

            current = current->paths[indx];
        }

        return start;
    }

    

}; // Trie


#endif