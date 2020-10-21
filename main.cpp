

//void Logger::#include <iostream>
#include <sstream>
#include "Logger.h"

using namespace std;
using namespace CPlusPlusLogging;

int main()
{
  std::cout << "LumberingGreenyellowCryptocurrency" << std::endl;

  LOG_ALWAYS("<=============================== START OF PROGRAM ===============================>");
  // Log message using Direct Interface
  // Log Level: LOG_ERROR
  LOG_ERROR("Message Logged using Direct Interface, Log level: LOG_ERROR");
  LOG_ALARM("Message Logged using Direct Interface, Log level: LOG_ALARM");
  LOG_ALWAYS("Message Logged using Direct Interface, Log level: LOG_ALWAYS");
  LOG_INFO("Message Logged using Direct Interface, Log level: LOG_INFO");
  LOG_DEBUG("Message Logged using Direct Interface, Log level: LOG_DEBUG");

  // Log message C++ Interface
  Logger* pLogger = NULL; // Create the object pointer for Logger Class
  pLogger = Logger::getInstance();

  // Log Variables
  std::string name = "Vikas Giridhar";
  std::string address = "Bengaluru, India";

  std::ostringstream ss;
  ss << endl;
  ss << "\t" << "My Contact Details:" << endl;
  ss << "\t" << "Name: " << name << endl;
  ss << "\t" << "Address: " << address << endl;

  //pLogger->enableConsoleLogging();
  pLogger->updateLogLevel(LOG_LEVEL_INFO);

  // Log ostringstream ss to all the log levels
  LOG_ALWAYS("Logging ostringstream using Direct Interface");
  LOG_ERROR(ss);
  LOG_ALARM(ss);
  LOG_ALWAYS(ss);
  LOG_INFO(ss);
  LOG_DEBUG(ss);
  
  LOG_ALWAYS("<=============================== END OF PROGRAM ===============================>");
  
  return 0;
}