#include <iostream>
#include <string>
#include <cstdlib>
#include "stack.hpp"

int main(int argc, char *argv[])
{
	try{
		Stack<int> intStack;
		Stack<std::string> stringStack;
		intStack.push(7);
		
		std::cout<<intStack.top()<< std::endl;
		
		stringStack.push("Hello");
		
		std::cout<<stringStack.top()<< std::endl;
		
		stringStack.pop();
		stringStack.pop();
		
	}
	catch(std::exception const& ex){
		std::cerr<<"Exception: "<< ex.what()<< std::endl;
		return EXIT_FAILURE;
		
	}
}