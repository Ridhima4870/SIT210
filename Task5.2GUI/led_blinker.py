import RPi.GPIO as GPIO   # Import library to control Raspberry Pi GPIO pins
import tkinter as tk      # Import Tkinter library to build GUI (Graphical User Interface)

# ---------------- GPIO Setup ----------------
GPIO.setmode(GPIO.BCM)    # Use BCM pin numbering (GPIO numbers instead of physical pin numbers)

# Define GPIO pin numbers for LEDs
RED = 17
GREEN = 27
BLUE = 22

# Setup the defined pins as OUTPUT pins (so we can send signals to them)
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(GREEN, GPIO.OUT)
GPIO.setup(BLUE, GPIO.OUT)

# ---------------- LED Control Functions ----------------
# Function to turn OFF all LEDs (so only one stays ON at a time)
def all_off():
    GPIO.output(RED, GPIO.LOW)
    GPIO.output(GREEN, GPIO.LOW)
    GPIO.output(BLUE, GPIO.LOW)

# Function to turn ON Red LED and turn others OFF
def red_on():
    all_off()                  # First turn everything OFF
    GPIO.output(RED, GPIO.HIGH)  # Then turn Red LED ON

# Function to turn ON Green LED and turn others OFF
def green_on():
    all_off()
    GPIO.output(GREEN, GPIO.HIGH)

# Function to turn ON Blue LED and turn others OFF
def blue_on():
    all_off()
    GPIO.output(BLUE, GPIO.HIGH)

# Exit function to safely close the program
def close():
    all_off()       # Turn all LEDs OFF before closing
    GPIO.cleanup()  # Reset GPIO pins (good practice to avoid errors later)
    root.destroy()  # Close the Tkinter window

# ---------------- Tkinter GUI Setup ----------------
root = tk.Tk()              # Create the main application window
root.title("LED Controller")  # Set the title of the window

# Add a label (text) at the top of the window
label = tk.Label(root, text="Select LED to turn ON:", font=("Arial", 12))
label.pack(pady=10)   # Place it in the window with some padding

# Create a Tkinter variable to keep track of which LED is selected
led_choice = tk.StringVar(value="off")

# Add 3 radio buttons, each linked to a different LED function
tk.Radiobutton(root, text="Red LED", variable=led_choice, value="red", command=red_on).pack(anchor=tk.W)
tk.Radiobutton(root, text="Green LED", variable=led_choice, value="green", command=green_on).pack(anchor=tk.W)
tk.Radiobutton(root, text="Blue LED", variable=led_choice, value="blue", command=blue_on).pack(anchor=tk.W)

# Add an Exit button to close the program
exit_btn = tk.Button(root, text="Exit", command=close, bg="red", fg="white")
exit_btn.pack(pady=10)

# ---------------- Run the Application ----------------
root.mainloop()   # Start the Tkinter event loop (keeps the window open until closed)
