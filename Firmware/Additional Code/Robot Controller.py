"""!
@file robot_controller.py
@brief A Python program for manual control of a differential drive robot.
@details This program was developed for the ME 507 class in Spring 2025 at Cal Poly.
         It reads keystrokes from the keyboard and transmits them via Bluetooth
         to the HC-05 module on the robot, which controls wheel movement.

@author Jack Maxwell
@date 2025-06-10
"""

import serial
import keyboard
import time
import serial.tools.list_ports

## Check if COM5 is available for HC-05 Bluetooth communication
available_ports = [port.device for port in serial.tools.list_ports.comports()]
if 'COM5' not in available_ports:
    print("COM5 is not available. Is the HC-05 powered on?")
else:
    try:
        ## Establish serial connection to HC-05 on COM5
        with serial.Serial('COM5', 115200, timeout=1, write_timeout=1) as ser:
            print("Serial port opened. Press arrow keys to control the robot. Press ESC to exit.")

            while True:
                try:
                    ## Send movement command based on keyboard input
                    if keyboard.is_pressed('up'):
                        ser.write(b'F\r\n')             #: Forward
                        print("Forward")
                    elif keyboard.is_pressed('down'):
                        ser.write(b'B\r\n')             #: Backward
                        print("Backward")
                    elif keyboard.is_pressed('left'):
                        ser.write(b'L\r\n')             #: Left
                        print("Left")
                    elif keyboard.is_pressed('right'):
                        ser.write(b'R\r\n')             #: Right
                        print("Right")
                    elif keyboard.is_pressed('esc'):
                        print("ESC pressed. Exiting...") #: Exit command
                        break
                    else:
                        ser.write(b'S\r\n')             #: Stop if no key is pressed

                    time.sleep(0.1)  #: Delay for responsiveness

                except (serial.SerialTimeoutException, serial.SerialException, OSError) as e:
                    print(f"Connection lost or write failed: {e}")
                    break

    except serial.SerialException as e:
        print(f"Failed to open serial port: {e}")

    except KeyboardInterrupt:
        print("KeyboardInterrupt received. Exiting...")

    except Exception as e:
        print(f"Unexpected error: {e}")

print("Program ended.")
