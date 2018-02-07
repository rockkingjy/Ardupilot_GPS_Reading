## OpenKAI_GPS_Reading
Modify OpenKAI to read GPS data from pixhawk2 + Ardupilot + GPS/Compass.


## Add a class in OpenKAI

Take the example of add _GPS_my.h in /OpenKAI/src/Navigation/:

1. Put the _GPS_my.cpp and _GPS_my.h in the folder /OpenKAI/src/Navigation/.

2. Chage in _GPS_my.h to(already done):
```
#ifndef SRC_NAVIGATION_GPS_MY_H_
#define SRC_NAVIGATION_GPS_MY_H_
```
3. Add in /OpenKAI/src/Config/Module.h:
```
#include "../Navigation/_GPS_my.h"
```
and add in /OpenKAI/src/Config/Module.cpp:
```
ADD_MODULE(_GPS_my);
```
4. Put the GPS_my.kiss in /OpenKAI/kiss:

5. Run:
```
make clean
ccmake ../
make -4j
sudo ./OpenKAI ../kiss/GPS_my.kiss
```
