/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include<string>

/* 
 * Class that describes a passenger, with name, surname, flag that indicates ability to drive
 */
class Passenger {

public: 
  /**
   * Constructor for a Passenger object
   * It is explicit to avoid unwanted implicit conversions
   * @param name string with the name of the Passenger
   * @param surname string with the surname of the Passenger
   * @param drive_flag bool that says if a passenger can drive or no
   */
  explicit Passenger(const std::string& name, const std::string& surname,  
  	bool drive_flag);

  ~Passenger();

  /**
   * Get the Passenger name
   * @return a string with the Passenger name
   */
  std::string getName() const;

  /**
   * Get the Passenger surname
   * @return a string with the Passenger surname
   */
  std::string getSurname() const;

  /**
   * Get the Passenger ability of driving
   * @return a boolean
   */
  bool getCanDrive() const;

  /**
   * Set the name
   * @param nm string with the name
   */
  void setName(const std::string& nm);

  /**
   * Set the surname
   * @param sn string with the surname
   */
  void setSurname(const std::string& sn);

  /**
   * Set the drive ability
   * @param drive_flag bool that says if a passenger can drive or no
   */
  void setCanDrive(bool drive_flag);

private: // private members
  std::string m_name; /**<name of the Passenger*/
  std::string m_surname; /**<surname of the Passenger*/
  bool m_candrive; /**<Can the Passenger drive?*/
};