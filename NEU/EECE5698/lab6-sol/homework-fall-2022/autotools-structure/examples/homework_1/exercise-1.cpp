/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

// this include was missing!
#include <iostream>

struct Trivial {
  int a; 
  Trivial(int aa) : a(aa) { } 
  Trivial() = default; // use the compiler generated 
                       // constructor
};

// do not modify the enumerators, find some other way
enum NotScoped {green, blue, red};
enum class SameEnumerators {green, yellow};

int main(int argc, char* argv[])
{
  // there are different ways to fix this, I just picked one for this example
  signed int unsigned_integer_variable {-10};
  int short_variable {90000};

  std::cout << "unsigned_integer_variable " << unsigned_integer_variable
    << " short_variable " << short_variable << std::endl;

  void* pointer {&unsigned_integer_variable};
  std::cout << "pointer content " << pointer << std::endl;
  // cannot dereference a void* 
    // << " value pointed by pointer " << *pointer << std::endl;

  const char* p = "northeastern";
  std::cout << "before modification " << *p << std::endl;
  // if p is a const char, it cannot be modified
  // (*p) = 'c';
  std::cout << "after modification " << *p << std::endl;

  Trivial structure{10};
  Trivial* ptr_struct{&structure};

  std::cout << "Value in struct " << structure.a 
    << " with pointer " << ptr_struct->a << std::endl;
 
  return 0;
}
