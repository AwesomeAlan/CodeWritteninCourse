/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <iostream>

struct Trivial {
  int a; 
  Trivial(int aa) : a(aa) { } 
  Trivial() = default; // use the compiler generated 
                       // constructor
};

// do not modify the enumerators, find some other way
enum class NotScoped {green, blue, red};
enum class SameEnumerators {green, yellow};

int main(int argc, char* argv[])
{
  signed int signed_integer_variable {-10};
  int short_variable = 90000; //-2^15 ~ 2^15 - 1

  std::cout << "unsigned_integer_variable " << signed_integer_variable
    << " short_variable " << short_variable << std::endl;

  signed int* pointer {&signed_integer_variable};
  std::cout << "pointer content " << pointer 
    << " value pointed by pointer " << *pointer << std::endl;

  const char* p = "northeastern";
  std::cout << "before modification " << *p << std::endl;
  p = "c";
  std::cout << "after modification " << *p << std::endl;

  Trivial structure{10};
  Trivial* ptr_struct{&structure};

  std::cout << "Value in struct " << structure.a 
    << " with pointer " << ptr_struct->a << std::endl;
 
  return 0;
}
