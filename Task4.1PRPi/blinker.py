# blinker.py
# This program blinks an LED connected to Raspberry Pi GPIO pin 10 (BOARD numbering).

import RPi.GPIO as GPIO   # Import the GPIO library to control the Raspberry Pi's pins
import time               # Import the time library for delays

GPIO.setmode(GPIO.BOARD)  # Use physical pin numbering (BOARD mode)

led_pin = 10              # Assign the LED to physical pin 10 on the GPIO header

GPIO.setup(led_pin, GPIO.OUT)   # Set pin 10 as an output pin

try:
    print("LED blinking started. Press Ctrl+C to stop.")  # Inform user that blinking begins
    
    while True:                       # Infinite loop to keep LED blinking
        GPIO.output(led_pin, GPIO.HIGH)  # Turn LED ON
        time.sleep(0.5)                 # Wait 0.5 seconds
        GPIO.output(led_pin, GPIO.LOW)   # Turn LED OFF
        time.sleep(0.5)                 # Wait 0.5 seconds

except KeyboardInterrupt:             # Triggered when user presses Ctrl+C
    print("\nProgram stopped by user.") # Display stop message

finally:
    print("Cleaning up GPIO settings.") # Inform about GPIO reset
    GPIO.cleanup()                      # Reset all GPIO pins to safe state
