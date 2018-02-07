## GPS_Reading

### Use dronekit to read GPS
Use dronekit to read GPS data from pixhawk2 + Ardupilot + GPS/Compass.

0. First connect with the PC or Jetson TX1/2 by USB port. Run 
```
ll /dev
```
to find the corrcet port name (ttyACM0).

1. Install [dronekit](http://python.dronekit.io/guide/quick_start.html) according to the webpage.

2. Run dronkit_getGPS.py

### Use OpenKAI to read GPS
Modify OpenKAI to read GPS data from pixhawk2 + Ardupilot + GPS/Compass.

0. First connect with the PC or Jetson TX1/2 by USB port. Run 
```
ll /dev
```
to find the corrcet port name (in my PC is ttyACM0, if use Jetson TX2, sometimes need to build kernel and ttyACM Module with Nvidia Jetson TX2 [[web](www.jetsonhacks.com)]), and modify GPS_my.kiss:
```
	"portName":"/dev/ttyACM0",
	"baud":115200,
```
If Connect with Jetson TX1/2 by TELEM1(not USB), then change to:
```
	"portName":"/dev/ttyTHS1",
	"baud":921600,
```

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
