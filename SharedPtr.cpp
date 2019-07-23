
SharedPtr::SharedPtr(T *tPtr = nullptr) {

};

/*	
 +++++++ Copy Constructor +++++++
 */

SharedPtr::SharedPtr(SharedPtr& sharedPtrObj) {
	
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

T &SharedPtr::operator *() {
	return *ptr;
};

/*
 ++++++++ Overload Arrow Operator. ++++++++
 */

T *SharedPtr::operator ->() {
	
	return ptr;
};
