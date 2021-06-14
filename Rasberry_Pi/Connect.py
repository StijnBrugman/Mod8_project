import serial
import time
import threading


class Connect(threading.Thread):
    """
    nothing
    """
    def __init__(self, port_name):
        threading.Thread.__init__(self)
        print("Creating connection")
        self.arduino = serial.Serial(port_name, 9600, timeout = .1)
        print("Connection created")
        self.arduino.flushInput()
        print("flushed")

        self.running = True

    def run(self):
        while self.running:
            print(self.arduino.readline())

    def stop(self):
        self.running = False

    def read_data(self):
        return self.arduino.readline()

    def write_data(self, data):
        self.arduino.flushInput()

