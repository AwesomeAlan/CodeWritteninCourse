/* 
 * [2022] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <modem.h>
#include <sstream>
#include <string.h>

const std::string Modem::SET_TX_POWER = "set_tx_power,";
const std::string Modem::SET_BITRATE = "set_bitrate,";
const std::string Modem::SET_VERBOSE = "set_verbose,";
const std::string Modem::QUIT = "QUIT";
const std::string Modem::ERROR = "ERROR::CONFIGURE::FAILED";
const std::string Modem::SUCCESS = "CONFIGURE::SUCCEEDED";

Modem::Modem(unsigned int tx_pwr, unsigned int rate, bool verb)
:
tx_power{tx_pwr},
bitrate{rate},
verbose{verb},
config_counter{0}
{

}

bool Modem::configure(std::shared_ptr<std::array<char, MTU>> buffer, size_t input_size, 
  size_t& output_size, bool& is_exit) 
{
  int success = parse(std::string {buffer->data(),input_size},is_exit);
  if(success) {
  	config_counter++;
  }
  std::stringstream sstm;
  if(verbose) {
    sstm << "[config_counter = " << config_counter << "],[tx_power=" << tx_power << "],[bitrate=" 
         << bitrate << "][verbose=" << verbose <<"]::";
  }
  if(success) {
    sstm << SUCCESS << std::endl;
  } else {
    sstm << ERROR << std::endl;
  }
  std::string return_string = sstm.str();
  memset(buffer->data(),0,MTU); 
  memcpy(buffer->data(),return_string.c_str(),return_string.size());
  output_size = return_string.size();
  return success;
}

bool Modem::parse(const std::string& configuration, bool& is_exit) 
{
  bool succeeded = false;
  size_t begin;
  char* end = nullptr;
  // this method checks which configuration has to be applied, by using
  // the find() method of a string object representing the configuration, 
  // that provides either the position where a certain configuration string 
  // is found, or the total size of the string if that specific configuration 
  // is not found
  if((begin = configuration.find(SET_TX_POWER)) < configuration.size()) {
    begin += SET_TX_POWER.size();
    // strtol convert a string to long int and sets the last position of the
    // long int to the "end" pointer. If "end" points to the same position of
    // "configuration.c_str()+begin", it means the convertion failed
    long int val = strtol(configuration.c_str()+begin,&end,10);
    if(end != configuration.c_str()+begin && val >= 0) {
      tx_power = val;
      succeeded = true;
    }
  }

  // EXERCISE 6: Implement the SET_BITRATE configuration, that sets the new
  // bitrate of the modem, only if the bitrate is a valid number >= 0. To this
  // aim, you can check the code of the SET_TX_POWER configuration.
  if((begin = configuration.find(SET_BITRATE)) < configuration.size()) {
    begin += SET_BITRATE.size();
    long int val = strtol(configuration.c_str()+begin,&end,10);
    if(end != configuration.c_str()+begin && val >= 0) {
      bitrate = val;
      succeeded = true;
    }
  }
  
  if((begin = configuration.find(SET_VERBOSE)) < configuration.size()) {
    begin += SET_VERBOSE.size();
    long int val = strtol(configuration.c_str()+begin,&end,10);
    if(end != configuration.c_str()+begin && (val == 0 || val == 1)) {
      verbose = val;
      succeeded = true;
    } 
  }
  if((begin = configuration.find(QUIT)) < configuration.size()) {
    is_exit = true;
    succeeded = true;
  }
  return succeeded;
}

// Exercise 2: implement the getTxPower and getBitrate methods
unsigned int Modem::getTxPower() const {
  return tx_power;
}

unsigned int Modem::getBitrate() const {
  return bitrate;
}

bool Modem::getVerbose() const
{
  return verbose; 
}

unsigned int Modem::getConfigurationsCounter() const
{
  return  config_counter;
}