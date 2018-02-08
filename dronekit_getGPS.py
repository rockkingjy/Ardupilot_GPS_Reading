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
print(ori + " created.")


portIndex = 0
while(1):
    try:
        vehicle = connect('/dev/ttyACM'+str(portIndex), wait_ready=True, baud=57600)
        print("Port "+str(portIndex)+" connected.")
        break
    except:
        print("OOOps...disconnected.")
        portIndex = 1 - portIndex
        time.sleep(2)
        continue


while(1):
    if os.path.exists("/dev/ttyACM"+str(portIndex)):
        current_millitime = int(round(time.time() * 1000))
        lat = vehicle.location.global_frame.lat
        lon = vehicle.location.global_frame.lon
        heading = vehicle.heading
        print(current_millitime,lat,lon,heading)
        f.write(str(current_millitime)+':'+str(lat)+','+str(lon)+','+str(heading)+'\n')
        f.flush()
        time.sleep(0.5)
    else:
        vehicle.close()
        while(1):
            try:
                print("Try to connect again.")
                vehicle = connect('/dev/ttyACM'+str(portIndex), wait_ready=True, baud=57600)               
                print("Port "+str(portIndex)+" connected.")
                break
            except:
                print("OOOps...disconnected.")     
                vehicle.close()
                portIndex = 1 - portIndex
                time.sleep(2)
                continue
