import time
import os.path
from dronekit import Vehicle,connect

#time.sleep(20)

directory = "/home/nvidia/GPS/"
ori = "/home/nvidia/GPS/gps.txt"

if not os.path.exists(directory):
    os.makedirs(directory)
i = 0
ori = directory + "gps" + str(i) + ".txt"
while os.path.isfile(ori):
    i = i + 1
    ori = directory + "gps" + str(i) + ".txt"

f = open(ori, 'a')
print(ori+" created.")

vehicle = connect('/dev/ttyACM0', wait_ready=True, baud=57600)

while(1):
    current_millitime = int(round(time.time() * 1000))
    lat = vehicle.location.global_frame.lat
    lon = vehicle.location.global_frame.lon
    heading = vehicle.heading
    print(current_millitime,lat,lon,heading)
    f.write(str(current_millitime)+':'+str(lat)+','+str(lon)+','+str(heading)+'\n')
    f.flush()
    time.sleep(0.5)

