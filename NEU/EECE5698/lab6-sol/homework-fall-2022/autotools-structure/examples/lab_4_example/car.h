/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#ifndef CAR_H
#define CAR_H

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


/**
 * The C++ class Car is a user-defined type to represent 
 * a Car. This class owns resources, i.e., the passengers 
 * are created in this class as pointers, and need to be handled
 * correctly when copying or destroying a Car object
 */
class Car : public VehicleInterface {

public: // public interface
	/**
	 * Constructor for a Car object
	 * It is explicit to avoid unwanted implicit conversions
	 * @param plates string to represent the plates for the class, with default empty string
	 */
	explicit Car(const int maximum_number_passengers, const std::string& plate = "");

	/**
	 * Copy constructor: needs to cope with pointers
 	 * @param car_to_copy a const lvalue ref to a Car object
	 */
	Car(const Car& car_to_copy);

	/**
	 * Copy assignment: needs to cope with pointers
	 * @param car_to_copy a const lvalue ref to a Car object
     * @return an lvalue ref to the copied object
	 */
  	Car& operator=(const Car& car_to_copy);

  	/**
  	 * Destructor - needs to cope with memory resources
  	 */
  	~Car();

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
	 * Get the plate
	 * @return a string with the plate
	 */
	std::string getPlates() const;

	/**
	 * Set the plate name
	 * @param a string with the plate
	 */
	void setPlates(const std::string& plates);

    /**
	 * Set the max_passengers limit 
	 * @param mx_pass int with the max passengers limit
	 */
	void setMaxPass(int maximum_number_passengers);

	// modifying functions to change the Car
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
	std::string m_plates; /**<plates of the Car */
    int m_max_passengers;
};


}; // end of namespace Vehicle

#endif // CAR_H

