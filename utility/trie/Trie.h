#ifndef TRIE_H

#define TRIE_H

#include <string>
#include "../shared_ptr/SharedPtr.h"



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

    struct Node {

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

    }; // Node;


    /*
     +++++ Pointer to the begining of the Trie +++++
     */

    SharedPtr<Node> head;

    /*
     ++++ Returns unique key ++++
     */

    size_t hash(char letter) const {

        return letter - '!';
    }


    /*
     +++++ Returns the destination Node +++++
     */

    SharedPtr<Node> goTo(size_t indx) const {

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
    };


    /*
     +++++ Returns the destination Node +++++
     */

    SharedPtr<Node> goTo(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const {
    
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
    };



public:
   


    /*
     +++ Main C'tor +++
     */

    Trie()

        :head(nullptr)
    {}

    /* 
     +++++ Stores data at the destination mapped with str. Params are forwarded to type T C'tor to create the data +++++
     */

    template<typename ... Params>

    void push(const std::string &str, Params&& ... params) {


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

    void push(size_t indx, const SharedPtr<T> &data) {

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

    SharedPtr<T> map(const std::string &data,  std::string::size_type start = 0, std::string::size_type end = 0) const {

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

    SharedPtr<T> map(size_t indx) const {

        /*
         +++++ Check if Node exist before dereferencing pointer +++++
         */ 
        if(SharedPtr<Node> nodePtr = goTo(indx))
            /*
             +++++ Return pointer to T in Node +++++
             */
            return nodePtr->tPtr;

        return nullptr;
    };

    /*
     +++++ Goes to destination and sets data to nullptr +++++
     */

    void eraseData(size_t indx) {
        goTo(indx)->tPtr = nullptr;
    };

    /*
     +++++ Goes to destination and sets data to nullptr +++++
     */

    void eraseData(const std::string &str) {
        goTo(str)->tPtr = nullptr;
    };


    /*
     +++++ Finds the position of input string where mapping broke off. +++++
     +++++ ie:  Map In Trie -> "HELLO",  Input -> "HEL", Output -> 3   +++++
     */

    std::string::size_type getBreakPoint(const std::string &data, std::string::size_type start = 0) const {

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
    };
    
}; // Trie




#endif