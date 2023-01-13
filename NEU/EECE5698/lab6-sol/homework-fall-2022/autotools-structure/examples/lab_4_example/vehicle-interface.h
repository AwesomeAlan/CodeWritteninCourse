/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese
*/

#ifndef VEHICLE_INTERFACE_H
#define VEHICLE_INTERFACE_H

#include <vector>
#include <string>
#include "passenger.h"

/**
 * The namespace Vehicle defines useful names to handle 
 * passengers inside a vehicle
 */
namespace Vehicle
{

using PassengerList = std::vector<Passenger*>;

/**
 * Interface for a vehicle
 */
class VehicleInterface {

public:
	/**
	 * Virtual destructor. It is important to 
	 * declare a destructor of a base class as virtual
	 */
	virtual ~VehicleInterface() {};

	/**
	 * Get the number of Passengers
	 * @return the number of registered Passengers
	 */
	virtual int getNumberOfPassengers() const = 0;

	/**
	 * Get the maximum number of Passengers
	 * @return the maximum number of Passengers
	 */
	virtual int getMaxNumberOfPassengers() const = 0;

	/**
	 * Get the list of Passengers
	 * @return a vector with the Passengers names
	 */
	virtual PassengerList getPassengerNames() const = 0;

	/**
	 * Add a Passenger
	 * @param pass_name the passenger name
	 * @param pass_surname the passenger surname
	 * @param drive_flag a boolean which indicates if the passenger can drive or not
	 */
	virtual void createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag) = 0;

	/**
	 * Print relevant information to a stream
	 * @param out an std::stream
	 */
	virtual void print(std::ostream& out) const = 0;
};


/**
 * Overleaded stream operator
 */
std::ostream& operator<<(std::ostream& out, const VehicleInterface& veh);

};

#endif // VEHICLE_INTERFACE_H