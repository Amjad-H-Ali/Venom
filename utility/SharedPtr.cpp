#include "SharedPtr.h"

/* 	
 +++++ Main C'tor +++++
 */

explicit SharedPtr::SharedPtr(T *tPtr = nullptr) 
    :sharedBy(nullptr)
{
    
    /*
     +++++ Initialize counter to 1 if tPtr is not nullptr +++++
     */

    if(tPtr) sharedBy = new unsigned(1);

    ptr = tPtr;
}

/*
 +++++ C'tor for Initialization to nullptr +++++
 */

SharedPtr::SharedPtr(const std::nullptr_t &nullObj) 
    :ptr(nullptr), sharedBy(nullptr)
{}


/*
 ++++++++++++++++
    Rule of 5
 ++++++++++++++++
 */


/* 1	
 +++++++ Copy C'tor +++++++
 */

SharedPtr::SharedPtr(const SharedPtr &sharedPtrObj) {

    
    /*	
     +++++ Copy resource and increment counter since this instance +++++
     +++++      shares same resource as object being copied.       +++++					
     */

    ptr = sharedPtrObj.ptr;

    sharedBy = sharedPtrObj.sharedBy;
    
    /*
     +++++ If ptr exist, sharedBy is guarenteed to exist as well. Increment it to +++++
     +++++     acknowledge that another object now shares the same resource.      +++++
     */

    if(ptr) ++(*sharedBy); 
};


/* 2
 ++++++ Destructor ++++++
 */

SharedPtr::~SharedPtr() {

    

    /*
     +++++ sharedBy is decremented. Resource is deleted   +++++
     +++++    if instance is the last one sharing it.     +++++ 
     */

    cleanUp();
};



/* 3
 ++++++ Move C'tor ++++++
 */

SharedPtr::SharedPtr(SharedPtr&& ptrObj) {

    

    /*
     ++++++ Steal resources and counter and set expiring instance's data ++++++
     ++++++   to nullptr. Epiring obj is safe to DEL (no memory leaks).  ++++++
     ++++++         It will not DEL resource shared by others.		    ++++++
     */

    ptr = ptrObj.ptr;

    ptrObj.ptr = nullptr;

    sharedBy = ptrObj.sharedBy;

    ptrObj.sharedBy = nullptr;

    /*
     +++++ Counter stolen from expiring object that will no longer  +++++
     +++++  share resource. Thus, sharedBy is not incremented here  +++++
     */
};


/* 4
 ++++++ Copy Assignment ++++++
 */

SharedPtr& SharedPtr::operator =(const SharedPtr &ptrObj) {

    /*
     +++++ sharedBy is decremented. Resource is deleted   +++++
     +++++    if instance is the last one sharing it.     +++++ 
     */

    cleanUp();

    /*
     +++++ Copy resources. +++++
     */

    ptr = ptrObj.ptr;

    sharedBy = ptrObj.sharedBy;

    /*
     +++++ Increment counter as this instance now +++++ 
     +++++ shares resource of object being copied.+++++
     */

    if(ptr) ++(*sharedBy);


    return *this;
};

/* 5
 +++++ Move Assignment +++++
 */

SharedPtr& SharedPtr::operator =(SharedPtr&& ptrObj) {

    

    /*
     +++++ sharedBy is decremented. Resource is deleted   +++++
     +++++    if instance is the last one sharing it.     +++++ 
     */

    cleanUp();

    

    /*
     +++++ Steal resource of expiring obj. +++++
     */

    ptr = ptrObj.ptr;

    sharedBy = ptrObj.sharedBy;

    ptrObj.ptr = nullptr;

    ptrObj.sharedBy = nullptr;

    /*
     +++++ Counter stolen from expiring object that will no longer  +++++
     +++++  share resource. Thus, sharedBy is not incremented here  +++++
     */


    return *this;
};


/*
 +++++ Assignment to nullptr +++++
 */

SharedPtr& SharedPtr::operator= (const std::nullptr_t &nullObj) {

    /*
     +++++ sharedBy is decremented. Resource is deleted   +++++
     +++++    if instance is the last one sharing it.     +++++ 
     */

    cleanUp();

    ptr = nullptr;

    sharedBy = nullptr;

    return *this;
}


/*
 ++++++++++++++++
    Overloads
 ++++++++++++++++
 */


/*
 +++++ Overload Dereference Operator. +++++
 */

inline T& SharedPtr::operator* () const {
    return *ptr;
};

/*
 +++++ Overload Arrow Operator. +++++
 */

inline T* SharedPtr::operator-> () const {
    return ptr;
};

/*
 +++++ Overload Comparison Operator. +++++
 */

inline bool SharedPtr::operator== (const std::nullptr_t &nullObj) const {
    return (ptr == nullptr); 
}

/*
 +++++ Overload Not Comparison Operator. +++++
 */

inline bool SharedPtr::operator!= (const std::nullptr_t &nullObj) const {
    return !(ptr == nullptr); 
}

/*
 +++++ Bool Convesion +++++
 */

inline operator bool() const {
    return ptr != nullptr;
}



/*
++++++ Deletes resource and sharedBy counter if this  ++++++
++++++ instance is the only one sharing that resource.++++++
*/

inline void SharedPtr::cleanUp() { 

    /*
     +++++ sharedBy is decremented. Resource is deleted   +++++
     +++++    if instance is the last one sharing it.     +++++ 
     */

    if(ptr && --(*sharedBy) == 0) {delete ptr; delete sharedBy;}
}