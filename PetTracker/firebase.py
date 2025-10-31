# Connect to Arduino via USB
# Read GPS data (like "LAT, LNG")
#  Upload the same to Firebase cloud

Connect to Arduino serial port
While receiving data:
   Read line
   Extract latitude and longitude
   Send the data to Firebase (and optionally to MQTT)
   Print "Data uploaded"
