/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese
*/

#include "vehicle-interface.h"

namespace Vehicle
{

std::ostream& operator<<(std::ostream& out, const VehicleInterface& veh)
{
	veh.print(out);
	return out;
};

}