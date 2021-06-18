from Settings import CONVERT_TO_CITY_DC, MIN_DISTANCE, MAX_DISTANCE, MAX_HEIGHT, MIN_HEIGHT, MESSAGES_DC, \
    WATER_HEIGHT_CONSTANT, INIT_WATER_HEIGHT, FLOW_MESSAGE, WATER_INTERVAL, DISTANCE_INTERVAL


class Distance():
    def __init__(self):
        self.raw_distance = {}
        self.distance = {}
        self.water_heights = {}
        self.temp = {}
        self.queue = []

        self.previous_messages = {}
        self.previous_water_message = None

        self.flow = {'flow_In': 0, 'flow_Out': 0}
        self.flow_init = {'flow_In': 0, 'flow_Out': 0}
        self.city_init = "Driel boven"
        self.date_init = None
        self.previous_date = None

        self.city = "Driel boven"

    def set_distance(self, distance):
        self.raw_distance = dict((CONVERT_TO_CITY_DC[key], value) for (key, value) in distance.items())
        # print(self.raw_distance)
        return self.raw_distance

    def set_flow(self, flow):
        self.flow = flow
        return self.flow

    def set_city(self, city):
        self.city = city
        return self.city

    def set_water_heights(self, water_heights):
        # print(water_heights)
        self.water_heights = water_heights
        return self.water_heights

    def set_temp(self, temp):
        # print(temp)
        self.temp = temp
        return self.temp

    def set_init_flow_data(self, flow, city):
        self.flow_init = flow
        self.city_init = city
        return self.flow_init, self.city_init

    def queue_is_empty(self):
        if not self.queue:
            return True
        return False

    def get_next_queue_message(self):
        return self.queue.pop(0)

    def add_to_queue(self, addition):
        if addition != b'':
            self.queue.append(addition)
        return self.queue

    def convert_height_to_distance(self):
        for key in self.water_heights:
            if self.water_heights.get(key) is None:
                continue
            distance_percentage = (self.water_heights[key] - MIN_HEIGHT[key]) / (MAX_HEIGHT[key] - MIN_HEIGHT[key])
            distance = MAX_DISTANCE - (MAX_DISTANCE - MIN_DISTANCE) * distance_percentage
            distance = min(distance, MAX_DISTANCE)
            distance = max(distance, MIN_DISTANCE)
            self.distance[key] = distance
        return self.distance

    def check_levels(self, distance):
        message = b""
        for key in distance:
            if distance.get(key) is None or self.raw_distance.get(key) is None or abs(
                    int(distance[key]) - self.raw_distance.get(key)) <= DISTANCE_INTERVAL:
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

    def flow_calc(self):
        message = b""
        # return if empty
        if not self.flow or not self.flow_init or not self.city_init:
            return message

        try:
            water_height = self.water_heights[self.city_init]
        except:
            return message

        if not water_height:
            # print(self.previous_water_message, message, self.date_init, self.previous_date)
            if self.previous_water_message !=  FLOW_MESSAGE['steady'] and self.date_init != self.previous_date:
                print("No data availbe")
                message += FLOW_MESSAGE['steady']
                print(message)
                self.previous_water_message = message
                self.previous_date = self.date_init
            return message

        water_height *= WATER_HEIGHT_CONSTANT
        current_water_height = self.flow['flow_In'] - self.flow['flow_Out'] + INIT_WATER_HEIGHT


        if current_water_height > water_height + WATER_INTERVAL:
            message += FLOW_MESSAGE['out']
        elif current_water_height < water_height - WATER_INTERVAL:
            message += FLOW_MESSAGE['in']
        else:
            message += FLOW_MESSAGE['steady']

        # print(current_water_height, water_height, message)
        # if no new data is send, dont add it to the message
        # print(message, self.previous_water_message)
        if self.previous_water_message == message and self.date_init == self.previous_date:
            message = b""
        else:
            self.previous_water_message = message
            self.previous_date = self.date_init
            print(message)
            print("water_height: ", water_height, current_water_height)
        return message

    def processing(self):
        self.distance = self.convert_height_to_distance()
        addition_message = self.flow_calc()
        message = addition_message
        self.add_to_queue(message)

    def set_init_date(self, date):
        self.date_init = date
        return self.date_init
