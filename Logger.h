
#ifndef _LOGGER_H_
#define _LOGGER_H_

// C++ Header File(s)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifdef WIN32
// Win Socket Header File(s)
#include <Windows.h>
#include <process.h>
#else
// POSIX Socket Header File(s)
#include <errno.h>
#include <pthread.h>
#endif

namespace CPlusPlusLogging
{
  // enum for LOG_LEVEL
  typedef enum LOG_LEVEL
  {
    DISABLE_LOG       = 1,
    LOG_LEVEL_INFO	  = 2,
    LOG_LEVEL_DEBUG   = 3,
    ENABLE_LOG        = 4,
  } LogLevel;

  class Logger
  {
  public:
    static Logger * getInstance() throw ();

    // Interface for Error Log 
    void error(const char * text) throw();
    void error(std::string & text) throw();
    void error(std::ostringstream & stream) throw();

    // Interface for Alarm Log 
    void alarm(const char * text) throw();
    void alarm(std::string & text) throw();
    void alarm(std::ostringstream & stream) throw();

    // Interface for Always Log 
    void always(const char * text) throw();
    void always(std::string & text) throw();
    void always(std::ostringstream & stream) throw();

    // Interface for Buffer Log 
    void buffer(const char * text) throw();
    void buffer(std::string & text) throw();
    void buffer(std::ostringstream & stream) throw();

    // Interface for Info Log 
    void info(const char * text) throw();
    void info(std::string & text) throw();
    void info(std::ostringstream & stream) throw();
    
    // Interface for Debug Log 
    void debug(const char * text) throw();
    void debug(std::string & text) throw();
    void debug(std::ostringstream & stream) throw();

    // Error and Alarm log must be always enable
    // Hence, there is no interfce to control error and alarm logs

    // Interfaces to control log levels
    void updateLogLevel(LogLevel logLevel);
    void enaleLog();  // Enable all log levels
    void disableLog(); // Disable all log levels, except error and alarm

protected:
  Logger();
  ~Logger();

  void lock();
  void unlock();

  std::string getCurrentTime();

private:
  Logger(const Logger& obj) {}
  void operator=(const Logger& obj) {}

private:
  static Logger*          m_Instance;
  std::ofstream           m_File;

#ifdef	WIN32
  CRITICAL_SECTION        m_Mutex;
#else
  pthread_mutexattr_t     m_Attr; 
  pthread_mutex_t         m_Mutex;
#endif

  LogLevel                m_LogLevel;
};

  // Direct Interface for logging into log file or console using MACRO(s)
  #define LOG_ERROR(x)    Logger::getInstance()->error(x)
  #define LOG_ALARM(x)	  Logger::getInstance()->alarm(x)
  #define LOG_ALWAYS(x)	  Logger::getInstance()->always(x)
  #define LOG_INFO(x)     Logger::getInstance()->info(x)
  #define LOG_DEBUG(x)    Logger::getInstance()->debug(x)

} // End of namespace

#endif // End of _LOGGER_H_
