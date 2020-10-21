
//#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Logger.h"

using namespace std;
using namespace CPlusPlusLogging;

Logger* Logger::m_Instance = 0;

// Log file name. File name should be change from here only
const string logFileName = "MyLogFile.log";

Logger::Logger()
{
  m_File.open(logFileName.c_str(), ios::out|ios::app);
  m_LogLevel	= LOG_LEVEL_INFO;

  // Initialize mutex
#ifdef WIN32
  InitializeCriticalSection(&m_Mutex);
#else
  int ret=0;
  ret = pthread_mutexattr_settype(&m_Attr, PTHREAD_MUTEX_ERRORCHECK_NP);
  if(ret != 0)
  {   
    printf("Logger::Logger() -- Mutex attribute not initialize!!\n");
    exit(0);
  }   
  ret = pthread_mutex_init(&m_Mutex,&m_Attr);
  if(ret != 0)
  {   
    printf("Logger::Logger() -- Mutex not initialize!!\n");
    exit(0);
  }   
#endif
}	

Logger::~Logger()
{
  m_File.close();
#ifdef WIN32
  DeleteCriticalSection(&m_Mutex);
#else
  pthread_mutexattr_destroy(&m_Attr);
  pthread_mutex_destroy(&m_Mutex);
#endif
}

Logger * Logger::getInstance() throw ()
{
  if (m_Instance == 0) 
  {
    m_Instance = new Logger();
  }
  return m_Instance;
}

void Logger::lock()
{
#ifdef WIN32
  EnterCriticalSection(&m_Mutex);
#else
  pthread_mutex_lock(&m_Mutex);
#endif
}

void Logger::unlock()
{
#ifdef WIN32
  LeaveCriticalSection(&m_Mutex);
#else
  pthread_mutex_unlock(&m_Mutex);
#endif
}
