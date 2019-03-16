// time_point constructors
#include <iostream>
#include <chrono>
#include <ctime>
 
int main ()
{
  using namespace std::chrono;
 
  system_clock::time_point tp_epoch;    // epoch value
 
  time_point <system_clock,duration<int> > tp_seconds (duration<int>(1));
 
  system_clock::time_point tp (tp_seconds);
 
  std::cout << "1 second since system_clock epoch = ";
  std::cout << tp.time_since_epoch().count();
  std::cout << " system_clock periods." << std::endl;
 
  // display time_point:
  std::time_t tt = system_clock::to_time_t(tp);
  std::cout << "time_point tp is: " << ctime(&tt);
 
  //2016-10-01 00:00:00
  struct tm ep_tm = {0};

  ep_tm.tm_year = 116; 	//2016
  ep_tm.tm_mon = 9;
  ep_tm.tm_mday = 1;
  ep_tm.tm_isdst = 0;

  std::time_t ep_t = mktime(&ep_tm);
  std::cout << asctime(&ep_tm);

  //std::cout << ep_t.tv_sec * 1000 + ep_t.tv_usec / 1000;
  std::cout << ep_t / 3600 / 24 / 365;

  system_clock::time_point tp1 = system_clock::from_time_t (ep_t);
  system_clock::duration d = system_clock::now() - tp1;
  
  std::cout << duration_cast<milliseconds> (d).count() << std::endl;

  return 0;
}

