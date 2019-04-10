#include <iostream>

using namespace std;
int arr[3] = {1,2,3};
class node {
public:
	int id;
	int *arr_ptr;
};

int main() {

	node n;
	n.id= 567;
	n.arr_ptr= arr;

	node *ptr = &n;

	


	



	cout << n.arr_ptr[0] << "\n";


	
}