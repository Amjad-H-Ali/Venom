
SharedPtr::SharedPtr(T *tPtr = nullptr) 
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

	++sharedBy;
};

/*
 ++++++ Destructor ++++++
 */

SharedPtr::~SharedPtr() {

	/*
	 +++++++++++ Decrement count of shared resources +++++++++++
	 */

	--sharedBy;

	/*
	 +++++++++++++++ Only delete if no other pointer is set to this resource +++++++++++++++
	 */

	if(sharedBy == 0) delete ptr;
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
