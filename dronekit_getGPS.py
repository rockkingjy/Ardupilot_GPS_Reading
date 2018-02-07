from dronekit import Vehicle,connect
vehicle = connect('/dev/ttyACM0', wait_ready=True, baud=57600)
lat = vehicle.location.global_frame.lat
lon = vehicle.location.global_frame.lon
heading = vehicle.heading
print(lat)
print(lon)
print(heading)
