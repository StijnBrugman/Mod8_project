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
        self.date = datetime.datetime(1950, 1, 1).strftime("%Y-%m-%d")

    def run(self):
        while self.running:
            # self.new_message = self.get_message()
            if self.different_message():
                try:
                    self.cnt.write_data(self.new_message)
                except:
                    print("ERROR")

    def stop(self):
        self.running = False


    def update_date(self, date):
        print(date)
        self.date = date
        return self.date

    def different_message(self):
        if self.old_message == self.new_message:
            return False
        self.old_message = self.new_message
        return True

    def set_message(self, message):
        self.new_message = message
        return self.new_message


