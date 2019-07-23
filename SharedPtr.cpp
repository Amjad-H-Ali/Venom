/* 	
 +++++++ Main C'tor +++++++
 */

explicit SharedPtr::SharedPtr(T *tPtr = nullptr) 
	:sharedBy(nullptr)
{
	/*
 	 ++++++++ If tPtr passed in is an actual resource and ++++++++
     ++++++++ not nullptr, initialize counter to 1. 	  ++++++++
 	 */

	if(tPtr) sharedBy = new unsigned(1);

	ptr = tPtr;
};

/*	
 +++++++ Copy Constructor +++++++
 */

SharedPtr::SharedPtr(const SharedPtr& sharedPtrObj) {

	/*	
	 +++++++ Copy resource and increment counter because another +++++++
	 +++++++ object now points to same resource. 				 +++++++					
	 */

	ptr = sharedPtrObj.ptr;

	sharedBy = sharedPtrObj.sharedBy;


	/*
	 ++++++ If ptr exist, then gaurenteed sharedBy exist and is 1 or greater. ++++++
	 */
	
	if(ptr) ++(*sharedBy);
};

/*
 ++++++ Destructor ++++++
 */

SharedPtr::~SharedPtr() {

	/*
	 ++++++++ If ptr is some resource, then we have a shared counter. ++++++++ 
	 ++++++++ After decrementing sharedBy and it's 0, then this was   ++++++++
	 ++++++++ the last instance pointing to that resource. So del.    ++++++++
	 */

    if(ptr && --(*sharedBy) == 0) { delete ptr; delete sharedBy;}

    /*
     +++++ An instance was destructed. So sharedBy was -- either way. +++++
     */
};

/*
 ++++++++++ Overload Dereference Operator. ++++++++++
 */

T &SharedPtr::operator *() const {
	return *ptr;
};

/*
 ++++++++ Overload Arrow Operator. ++++++++
 */

T *SharedPtr::operator ->() const {
	
	return ptr;
};
