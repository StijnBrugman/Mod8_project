import sys
from Rasberry_Pi.Connect import Connect
from Settings import BT_PORT_NAME, LIST_CITIES, colors
from Datastorage.storage import Storage
from Datastorage.dateConverter import Converter
from Rasberry_Pi.Sending import Sending
from Datastorage.Distance import Distance
from Datastorage.LCDSender import LCDSender

import time

if __name__ == '__main__':
    '''
    Setup
    '''
    stg = Storage()

    cnt = Connect(BT_PORT_NAME)
    cnt.start()

    snd = Sending(cnt)
    snd.start()

    distance_cv = Distance()

    date_cv = Converter()

    LCD_snd = LCDSender()

    index = 0

    program_running = True
    while program_running:
        # try:
        # if there is  new data, we store it, and translate it to the correct date


        if cnt.data_available():
            try:
                stg.store_data(cnt.get_new_data())
            except:
                print("TO MUCH DATA")

            if stg.is_date():
                date_cv.update_date(stg.get_raw_date())
                LCD_snd.set_date(date_cv.get_date())
                # print(date_cv.get_date())

            if stg.is_distance():
                distance_cv.set_distance(stg.get_distance_data())

            if stg.is_city():
                distance_cv.set_city(stg.get_city())
                LCD_snd.set_city(stg.get_city())

            if stg.is_flow():
                # print(stg.get_flow())
                distance_cv.set_flow(stg.get_flow())

            if stg.button_pressed():
                # distance_cv.add_to_queue(colors[index])
                # index += 5

                snd.update_date(date_cv.get_date())
                distance_cv.set_init_date(date_cv.get_date())
                water_heights = {}
                temperature = {}

                for city in LIST_CITIES:
                    water_heights[city] = stg.get_water(city, date_cv.get_date())
                    temperature[city] = stg.get_temp(city, date_cv.get_date())

                distance_cv.set_water_heights(water_heights)
                distance_cv.set_temp(temperature)
                print("------------- Button is Pressed -------------")
                distance_cv.processing()
                # print("Measured distance ", distance_cv.raw_distance)
                # print("Required distance ", distance_cv.distance)
                # print("Actual distance ", distance_cv.water_heights)

                # print(stg.get_water("Driel boven", date_cv.get_date()))
                # distance_cv.add_to_queue(b'O3,255,0,0\nP3,255,0,0\nQ3,255,0,0\nR3,255,0,0\nS3,255,0,0\n')

        # print(distance_cv.queue_is_empty())

        if not distance_cv.queue_is_empty():
            data = distance_cv.get_next_queue_message()
            print("data", data)
            snd.set_message(data)

        # Sending data for the LCD
        if not LCD_snd.queue_is_empty():
            snd.set_message(LCD_snd.get_next_queue_message())

    # except:
    # print("ERROR catched, closing program")

    # Closing all threats and closing the program
    program_running = False
    cnt.stop()
    snd.stop()
