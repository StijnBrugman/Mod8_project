from Settings import CONVERT_TO_CITY_DC, MIN_DISTANCE, MAX_DISTANCE, MAX_HEIGHT, MIN_HEIGHT, MESSAGES_DC

class Distance():
    def __init__(self):
        self.raw_distance = {}
        self.distance = {}
        self.water_heights = {}
        self.temp = {}
        self.queue = []

        self.previous_messages = {}

    def set_distance(self, distance):
        self.raw_distance = dict((CONVERT_TO_CITY_DC[key], value) for (key, value) in distance.items())
        # print(self.raw_distance)
        return self.raw_distance

    def set_water_heights(self, water_heights):
        # print(water_heights)
        self.water_heights = water_heights
        return self.water_heights

    def set_temp(self, temp):
        # print(temp)
        self.temp = temp
        return self.temp

    def queue_is_empty(self):
        if not self.queue:
            return True
        return False

    def get_next_queue_message(self):
        return self.queue.pop(0)

    def add_to_queue(self, addition):
        if addition != b'':
            self.queue.append(addition)
            print(self.queue)
        return self.queue

    def convert_height_to_distance(self):
        for key in self.water_heights:
            if self.water_heights.get(key) is None:
                continue
            distance_percentage = (self.water_heights[key]-MIN_HEIGHT) / (MAX_HEIGHT-MIN_HEIGHT)
            distance = MAX_DISTANCE - (MAX_DISTANCE-MIN_DISTANCE) * distance_percentage
            distance = min(distance, MAX_HEIGHT)
            distance = max(distance, MIN_DISTANCE)
            self.distance[key] = distance
        return self.distance

    def check_levels(self, distance):
        message = b""

        for key in distance:
            if distance.get(key) is None or self.raw_distance.get(key) is None or abs(int(distance[key]) - self.raw_distance.get(key)) <= 2:
                message_fragment = MESSAGES_DC[key][2]

                if message_fragment != self.previous_messages.get(key):
                    message += message_fragment
                    self.previous_messages[key] = message_fragment

                continue

            # Should lower water value
            if distance[key] > self.raw_distance[key]:
                message_fragment = MESSAGES_DC[key][1]

                if message_fragment != self.previous_messages.get(key):
                    message += message_fragment
                    self.previous_messages[key] = message_fragment
                continue

            message_fragment = MESSAGES_DC[key][0]
            if message_fragment != self.previous_messages.get(key):
                message += message_fragment
                self.previous_messages[key] = message_fragment

        return message

    def processing(self):
        self.distance = self.convert_height_to_distance()
        message = self.check_levels(self.distance)
        self.queue = self.add_to_queue(message)

