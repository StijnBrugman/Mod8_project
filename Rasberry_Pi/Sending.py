import threading
import datetime

class Sending(threading.Thread):
    def __init__(self, connection):
        threading.Thread.__init__(self)
        self.cnt = connection
        self.running = True
        self.queue = []
        self.new_message = None
        self.old_message = None
        self.date = datetime.datetime(1950, 1, 1)

    def run(self):
        while self.running:
            self.new_message = self.get_message()
            if self.different_message():
                self.cnt.write_data(self.new_message)

    def stop(self):
        self.running = False

    def update_date(self, date):
        self.date = date
        return self.date

    def different_message(self):
        if self.old_message == self.new_message:
            return False
        self.old_message = self.new_message
        return True

    def get_message(self):
        if self.date > datetime.datetime(2000, 1, 1):
            return [0,0,1]
        if self.date > datetime.datetime(1975, 1, 1):
            return [0,1,0]
        return [1,0, 0]


