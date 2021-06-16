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

            if stg.button_pressed():
                snd.update_date(date_cv.get_date())
                # print(stg.get_water("Driel boven", date_cv.get_date()))

            # Getting all the water_heights and temperatures for the correct date
            water_heights = {}
            # for place in ["Driel boven", ]

            distance_cv.set_distance(stg.get_distance_data())
        print(stg.get_water("Driel boven", date_cv.get_date()))

    cnt.stop()
    sys.exit()
