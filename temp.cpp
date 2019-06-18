// #include <iostream>
// #include <variant>



// typedef std::variant< std::nullptr_t, int *, float *, bool *, char *> var_t;


// template<typename ... Types> struct Overloads : Types ... {using Types::operator() ...;};
// template<typename ... Types> Overloads(Types ...) -> Overloads<Types ...>;


// template<typename ... T>
// // T = int * &, float * &
// decltype(auto) parse (T&& ... params) {

//     // params = int * &, float * &
// 	return std::visit(Overloads{

//         [](){return new bool(true);},

//         [](auto, auto){return new float(5.5);},

// 		[](auto){return (char*)"hello";},

// 		[](int*, float*){ return new int(5);},

// 	}, std::forward<T>(params)...);

// };


// int main(){

//     var_t i = new int(5);

//     var_t f = new float(5.f);

//     // var_t = int *, float *
//     // i and f are L-Values
//     std::cout << *parse(i, f) << std::endl;
// }