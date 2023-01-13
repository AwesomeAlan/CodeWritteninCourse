/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include "car.h"

namespace Vehicle {

Car::Car(const int mx_pass, const std::string& plates) : 
    m_passengers{}, 
	m_plates{plates},
	m_max_passengers{mx_pass}
{

}

Car::Car(const Car& car_to_copy) :
    m_passengers{}, // we do not want to copy the pointers, but the content of the pointers
    m_plates{car_to_copy.getPlates()}, // use get methods whenever you can, instead of plain access to variables
    m_max_passengers{car_to_copy.getMaxNumberOfPassengers()}
{
    // this is the piece of code that guarantees no shallow copy
    for (auto pass : car_to_copy.getPassengerNames())
    {
        // here, you can re-use a function rather than copying the same code twice!
        createPassenger(pass->getName(), pass->getSurname(), pass->getCanDrive());
    }
}

Car& 
Car::operator=(const Car& car_to_copy) 
{
    // clear the passengers list
    m_passengers.clear();
    setPlates(car_to_copy.getPlates());
    setMaxPass(car_to_copy.getMaxNumberOfPassengers());

    // this is the piece of code that guarantees no shallow copy
    for (auto pass : car_to_copy.getPassengerNames())
    {
        // here, you can re-use a function rather than copying the same code twice!
        createPassenger(pass->getName(), pass->getSurname(), pass->getCanDrive());
    }

    return *this;
}

Car::~Car()
{
    // we need to delete the memory that was created in this class
    for (auto pass : m_passengers) 
    {
        delete pass;
    }
}


int
Car::getNumberOfPassengers() const
{
	return m_passengers.size();
}

int
Car::getMaxNumberOfPassengers() const
{
    return m_max_passengers;
}

PassengerList
Car::getPassengerNames() const
{
	return m_passengers;
}

std::string 
Car::getPlates() const
{
	return m_plates;
}

void
Car::setPlates(const std::string& Plates)
{
	m_plates = Plates;
}

void
Car::setMaxPass(int mx_pass)
{
	m_max_passengers = mx_pass;
}

void
Car::createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag)
{
    if(m_passengers.size() < m_max_passengers) {
	    Passenger* pass = new Passenger{pass_name, pass_surname, drive_flag};
        m_passengers.push_back(pass);
    }
    else
    {
        // this is actually not a good practice: print to the terminal should not
        // go in the implementation of a class, but rather in the code that uses
        // the class. It would be better to return a bool, or throw an exception
        std::cout << "Passenger limit reached. Cannot add " << pass_name << std::endl;
    }
}

}
