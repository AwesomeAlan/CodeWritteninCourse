/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include "truck.h"

namespace Vehicle {

Truck::Truck(int mx_pass, double load) : 
    m_passengers{}, 
	m_max_load{load},
	m_max_passengers{mx_pass}
{

}

Truck::Truck(const Truck& truck_to_copy) :
    m_passengers{}, // we do not want to copy the pointers, but the content of the pointers
    m_max_load{truck_to_copy.getMaxLoad()}, // use get methods whenever you can, instead of plain access to variables
    m_max_passengers{truck_to_copy.getMaxNumberOfPassengers()}
{
    // this is the piece of code that guarantees no shallow copy
    for (auto pass : truck_to_copy.getPassengerNames())
    {
        // here, you can re-use a function rather than copying the same code twice!
        createPassenger(pass->getName(), pass->getSurname(), pass->getCanDrive());
    }
}

Truck& 
Truck::operator=(const Truck& truck_to_copy) 
{
    // clear the passengers list
    m_passengers.clear();
    setMaxLoad(truck_to_copy.getMaxLoad());
    setMaxPass(truck_to_copy.getMaxNumberOfPassengers());

    // this is the piece of code that guarantees no shallow copy
    for (auto pass : truck_to_copy.getPassengerNames())
    {
        // here, you can re-use a function rather than copying the same code twice!
        createPassenger(pass->getName(), pass->getSurname(), pass->getCanDrive());
    }

    return *this;
}

Truck::~Truck()
{
    // we need to delete the memory that was created in this class
    for (auto pass : m_passengers) 
    {
        delete pass;
    }
}


int
Truck::getNumberOfPassengers() const
{
	return m_passengers.size();
}

int
Truck::getMaxNumberOfPassengers() const
{
    return m_max_passengers;
}

PassengerList
Truck::getPassengerNames() const
{
	return m_passengers;
}

double
Truck::getMaxLoad() const
{
	return m_max_load;
}

void
Truck::setMaxLoad(double load)
{
	m_max_load = load;
}

void
Truck::setMaxPass(int mx_pass)
{
	m_max_passengers = mx_pass;
}

void
Truck::createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag)
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

void
Truck::print(std::ostream& out) const
{
    out << "Truck has max load " << getMaxLoad();
}

}
