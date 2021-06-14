import serial
from serial import SerialException
from serial.tools import list_ports
import time
import threading


class Connect(threading.Thread):
    """
    nothing
    """

    def __init__(self, port_name):
        threading.Thread.__init__(self)
        self.print_ports()
        print("Creating connection")
        self.running = True
        self.try_connection(port_name)

    def print_ports(self):
        for port in list_ports.comports():
            print('...' + str(port))

    def try_connection(self, port_name):
        try:
            self.arduino = serial.Serial(port_name, 9600, timeout=.1)
            print('Serial connection opened.')
        except SerialException:
            self.running = False
            print(
                'Serial connection could not be opened.\n...Please close the serial monitor if open.')

    def run(self):
        while self.running:
            print(self.arduino.readline())

    def stop(self):
        self.running = False

    def read_data(self):
        return self.arduino.readline()

    def write_data(self, data):
        self.arduino.flushInput()
