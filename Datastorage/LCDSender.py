from Settings import MESSAGES_LCD


class LCDSender():

    def __init__(self):
        self.queue_message = []
        self.set_city("Driel boven")


    def queue_is_empty(self):
        if not self.queue_message:
            return True
        return False

    def get_next_queue_message(self):
        print("queque", self.queue_message)
        return self.queue_message.pop(0)

    def set_date(self, date):
        print(date)
        message = MESSAGES_LCD['Date'] + bytes(date, 'utf-8') + b"\n"
        self.queue_message.append(message)
        return self.queue_message

    def set_city(self, city):
        message = MESSAGES_LCD['City'] + bytes(city, 'utf-8') + b"\n"
        self.queue_message.append(message)
        return self.queue_message
