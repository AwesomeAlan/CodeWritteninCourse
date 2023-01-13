/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include <string>
#include "passenger.h"
#include "vehicle-interface.h"

/**
 * The namespace Vehicle defines useful names to handle 
 * passengers inside a vehicle
 */
namespace Vehicle
{


// NOTE: this is probably not the best design for these two classes and interface
// but it is useful to provide you with an additional example


/**
 * The C++ class Truck is a user-defined type to represent 
 * a Truck. This class owns resources, i.e., the passengers 
 * are created in this class as pointers, and need to be handled
 * correctly when copying or destroying a Truck object
 */
class Truck : public VehicleInterface {

public: // public interface
	/**
	 * Constructor for a Truck object
	 * It is explicit to avoid unwanted implicit conversions
	 * @param max number of pass
	 * @param max load
	 */
	explicit Truck(int maximum_number_passengers, double load);

	/**
	 * Copy constructor: needs to cope with pointers
 	 * @param truck_to_copy a const lvalue ref to a Truck object
	 */
	Truck(const Truck& truck_to_copy);

	/**
	 * Copy assignment: needs to cope with pointers
	 * @param truck_to_copy a const lvalue ref to a Truck object
     * @return an lvalue ref to the copied object
	 */
  	Truck& operator=(const Truck& truck_to_copy);

  	/**
  	 * Destructor - needs to cope with memory resources
  	 */
  	~Truck();

	// non-modifying members to inspect a class
	/**
	 * Get the number of Passengers
	 * @return the number of registered Passengers
	 */
	int getNumberOfPassengers() const override;

	/**
	 * Get the maximum number of Passengers
	 * @return the maximum number of Passengers
	 */
	int getMaxNumberOfPassengers() const override;

	/**
	 * Get the list of Passengers
	 * @return a vector with the Passengers names
	 */
	PassengerList getPassengerNames() const override;

	/**
	 * Get the maximum load
	 * @return a double with the maximum load
	 */
	double getMaxLoad() const;

	/**
	 * Set the maximum load
	 * @param load a double with the maximum load
	 */
	void setMaxLoad(double load);

    /**
	 * Set the max_passengers limit 
	 * @param mx_pass int with the max passengers limit
	 */
	void setMaxPass(int maximum_number_passengers);

	// modifying functions to change the Truck
	/**
	 * Add a Passenger
	 * @param pass_name the passenger name
	 * @param pass_surname the passenger surname
	 * @param drive_flag a boolean which indicates if the passenger can drive or not
	 */
	void createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag) override;

	void print(std::ostream& out) const override;

private:
	PassengerList m_passengers; /**<list of pointers to Passenger objects */
    double m_max_load;
    int m_max_passengers;
};


}; // end of namespace Vehicle

#endif // TRUCK_H

