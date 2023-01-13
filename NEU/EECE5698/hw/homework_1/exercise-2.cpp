/*
 * [2022] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Michele Polese 
 */

// remember to use the relevant #include
#include <iostream>
#include <string>


// the binary generated from this C++ code should be called
// with at least one extra command line argument
// for example: /path/to/bin/exercise_2 extra_argument
int main (int argc, char* argv[])
{
	// declare an array of C-style strings (i.e., string literals) 
	// which should contain the command-line arguments (i.e., the elements of argv),
	// except for the name of this binary (i.e., argv[0])
	// the size of the array should adapt to the number of arguments
	// passed from the command line (i.e., use the variable argc)
	if (argc == 1) {
		return 0;
	}

	// initialize each entry in the array with the command-line arguments
	// (except for the name of the binary, which is the first entry in argv)
	char* entries[argc];
	for (int i = 1; i < argc; i++) {
		entries[i] = argv[i];
	}

	// print the content of the array to the terminal, one entry for each line
	// (without using argv, use the new array!)
	for (int i = 1; i < argc; i++) {
		for (int j = 0; entries[i][j] != '\0'; j++) {
			cout << entries[i][j];
		}
		cout << endl;
	}

	// print the first string literal in the array, one letter for each line
	for (int i = 0; entries[1][i] != '\0'; i++) {
		cout << entries[1][i] << endl;
	}
	
	return 0;
}