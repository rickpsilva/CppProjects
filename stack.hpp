#include <iostream>
#include <vector>
#include <stdexcept>

template<class T>
class Stack {
	public:
		Stack() = default;
		Stack(Stack<T> const&);
		Stack<T>& operator= (Stack<T> const &);
		
		void push(T const&);
		T pop();
		T top() const;
		bool empty() const {
			return elems.empty();
		}
	private:
		std::vector<T> elems;
};

template<typename T>
void Stack<T>::push(T const& elem){
	elems.push_back(elem);
}

template<typename T>
T Stack<T>::pop(){
	if(elems.empty()){
		throw std::out_of_range("Stack<>::pop: empty stack ");
	}
	T elem = elems.back();
	elems.pop_back();
	return elem;
}

template<typename T>
T Stack<T>::top() const{
	if(elems.empty()){
		throw std::out_of_range("Stack<>::top: empty stack ");
	}
	return elems.back();
}
