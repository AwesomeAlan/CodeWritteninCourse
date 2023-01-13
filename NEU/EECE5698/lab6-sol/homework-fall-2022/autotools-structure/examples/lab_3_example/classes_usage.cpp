/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include "car.h"

int
main(int argc, char const *argv[])
{
  Vehicle::Car car_1{5, "AABB33C"};

  // let's check that there are no Passengers
  std::cout << "Number of Passengers = " 
    << car_1.getNumberOfPassengers() << std::endl;
  // let's try to get the Plates name
  std::cout << "Plates name = "
    << car_1.getPlates() << std::endl;

  // add Passengers
  car_1.createPassenger("John", "Smith", true);
  car_1.createPassenger("Jane", "Doe", false);
    
  // create a const class and show that modifiers do not work
  // using the copy constructor
  const Vehicle::Car car_2{car_1};

  std::cout << "The plates in car_2 are " << car_2.getPlates() 
    << std::endl;

  // what do you think auto will translate to?
  auto list = car_2.getPassengerNames();
  // print them
  for (auto pass : list)
  {
    std::cout << pass->getName() << ", " << pass->getSurname() << std::endl;
  }

  return 0;
}
