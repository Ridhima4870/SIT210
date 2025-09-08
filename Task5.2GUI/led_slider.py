import RPi.GPIO as GPIO     # Library to control Raspberry Pi GPIO pins
import tkinter as tk        # Tkinter library to make a GUI window

# ---------------- GPIO Setup ----------------
GPIO.setmode(GPIO.BCM)      # Use BCM pin numbering (GPIO numbers instead of board pin numbers)

# Define GPIO pins for Red, Green, and Blue LEDs
RED, GREEN, BLUE = 17, 27, 22  

# Set these pins as output pins
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)
GPIO.setup(BLUE, GPIO.OUT)

# Setup PWM (Pulse Width Modulation) on each pin with frequency = 100 Hz
# PWM allows us to control brightness by changing duty cycle (0% = OFF, 100% = full ON)
red_pwm = GPIO.PWM(RED, 100)
green_pwm = GPIO.PWM(GREEN, 100)
blue_pwm = GPIO.PWM(BLUE, 100)

# Start PWM with 0% duty cycle (LEDs off)
red_pwm.start(0)
green_pwm.start(0)
blue_pwm.start(0)

# ---------------- Functions ----------------
# Function to set brightness of Red LED
def set_red(val):
    duty = int(val)                   # Convert slider value to integer
    red_pwm.ChangeDutyCycle(duty)     # Adjust duty cycle to change brightness

# Function to set brightness of Green LED
def set_green(val):
    duty = int(val)
    green_pwm.ChangeDutyCycle(duty)

# Function to set brightness of Blue LED
def set_blue(val):
    duty = int(val)
    blue_pwm.ChangeDutyCycle(duty)

# Function to safely exit the program
def close():
    # Stop all PWM signals
    red_pwm.stop()
    green_pwm.stop()
    blue_pwm.stop()
    GPIO.cleanup()    # Reset GPIO pins
    root.destroy()    # Close the GUI window

# ---------------- Tkinter GUI Setup ----------------
root = tk.Tk()                     # Create the main window
root.title("LED Brightness Control")  # Window title

# Add label on top of the window
label = tk.Label(root, text="Adjust LED Brightness:", font=("Arial", 12))
label.pack(pady=10)

# --- Red LED Slider ---
tk.Label(root, text="Red LED").pack()                       # Label
red_slider = tk.Scale(root, from_=0, to=100, orient="horizontal", command=set_red)
red_slider.pack()                                           # Horizontal slider (0–100%)

# --- Green LED Slider ---
tk.Label(root, text="Green LED").pack()
green_slider = tk.Scale(root, from_=0, to=100, orient="horizontal", command=set_green)
green_slider.pack()

# --- Blue LED Slider ---
tk.Label(root, text="Blue LED").pack()
blue_slider = tk.Scale(root, from_=0, to=100, orient="horizontal", command=set_blue)
blue_slider.pack()

# Exit button to close app safely
exit_btn = tk.Button(root, text="Exit", command=close, bg="red", fg="white")
exit_btn.pack(pady=10)

# ---------------- Run the Application ----------------
root.mainloop()   # Start Tkinter event loop (keeps window running)
