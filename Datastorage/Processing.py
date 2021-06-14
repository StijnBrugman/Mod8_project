import serial
import time
import threading
from Datastorage.storage import Storage


class Processing(threading.Thread):
    """
    nothing
    """
    def __init__(self):
        threading.Thread.__init__(self)
        self.running = True
        self.stg = Storage()

    def run(self):
        while self.running:
            pass

    def stop(self):
        self.running = False


