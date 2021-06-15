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
        self.new_data = None
        self.print_ports()
        print("Creating connection")
        self.running = True
        self.try_connection(port_name)
        self.queue = []

    def print_ports(self):
        for port in list_ports.comports():
            print('...' + str(port))

    def try_connection(self, port_name):
        try:
            self.arduino = serial.Serial(port_name, 9600, timeout=.1)
            print('Serial connection opened.')
            self.arduino.flushInput()
        except SerialException:
            self.running = False
            print(
                'Serial connection could not be opened.\n...Please close the serial monitor if open.')

    def run(self):
        while self.running:
            self.new_data = self.read_data()
            if self.new_data_available():
                self.queue.append(self.new_data)

    def stop(self):
        self.running = False

    def read_data(self):
        if not self.arduino.inWaiting():
            return None
        return self.arduino.readline().decode("utf-8").rstrip("\r\n")

    def new_data_available(self):
        # Check if there is new data to be analyzed, so no None object get added
        if self.new_data is None:
            return False
        return True

    def write_data(self, data):
        print(data)
        self.arduino.write(data)


    def get_new_data(self):
        # return first value in the queue
        return self.queue.pop(0)

    def data_available(self):
        # Check if there is stored data in the queue
        if not self.queue:
            return False
        return True


