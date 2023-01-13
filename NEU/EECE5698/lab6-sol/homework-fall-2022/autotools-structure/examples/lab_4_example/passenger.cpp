/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/


#include "passenger.h"

Passenger::Passenger(const std::string& name, const std::string& surname, bool drive_flag) :
	m_name{name},
	m_surname{surname},
	m_candrive{drive_flag}
{

}

Passenger::~Passenger() 
{
  
}

std::string
Passenger::getName() const 
{
  return m_name;
}

std::string
Passenger::getSurname() const
{
  return m_surname;
}

bool
Passenger::getCanDrive() const 
{
  return m_candrive;
}

void
Passenger::setName(const std::string& nm)
{
  m_name = nm;
}

void
Passenger::setSurname(const std::string& sn)
{
  m_surname = sn;
}

void
Passenger::setCanDrive(bool drive_flag) {
  m_candrive = drive_flag;
}
 