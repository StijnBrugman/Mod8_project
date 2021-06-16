import sys
from Rasberry_Pi.Connect import Connect
from Settings import BT_PORT_NAME, LIST_CITIES
from Datastorage.storage import Storage
from Datastorage.dateConverter import Converter
from Rasberry_Pi.Sending import Sending
from Datastorage.Distance import Distance

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

    program_running = True
    while program_running:
        # if there is  new data, we store it, and translate it to the correct date
        if cnt.data_available():
            stg.store_data(cnt.get_new_data())

            if stg.is_date():
                date_cv.update_date(stg.get_raw_date())

            if stg.is_distance():
                distance_cv.set_distance(stg.get_distance_data())

            if stg.button_pressed():
                snd.update_date(date_cv.get_date())

                water_heights = {}
                temperature = {}

                for city in LIST_CITIES:
                    water_heights[city] = stg.get_water(city, date_cv.get_date())
                    temperature[city] = stg.get_temp(city, date_cv.get_date())

                distance_cv.set_water_heights(water_heights)
                distance_cv.set_temp(temperature)

                # print(stg.get_water("Driel boven", date_cv.get_date()))
        distance_cv.processing()
        # print(distance_cv.queue_is_empty())
        if not distance_cv.queue_is_empty():
            snd.set_message(distance_cv.get_next_queue_message())

        # Getting all the water_heights and temperatures for the correct date









    cnt.stop()
    sys.exit()
