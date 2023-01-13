/*
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Michele Polese 
 */

#include <iostream>

int main (int argc, char* argv[])
{
	if (argc == 1) {
		return 0;
	}

	const int size = argc - 1;
	// declare an array of C-style strings (i.e., string literals) 
	// which should contain the command-line arguments, except for the
	// name of this binary
	const char* array[size];

	// initialize each entry in the array with the command-line arguments
	// (except for the name of the binary, which is the first entry in argv)
	for(int i = 1; i < argc; ++i)
	{
		array[i - 1] = argv[i];
	}

	// print the content of the array to the terminal, one entry for each line
	// (without using argv!)
	for (int i = 0; i < size; ++i)
	{
		std::cout << array[i] << std::endl;
	}

	// print the first string literal in the array, one letter for each line
	const char* str = array[0];

	for(; *str != '\0'; ++str)
	{
		std::cout << *str << std::endl;
	}

}