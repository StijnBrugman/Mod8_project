import sys
from Rasberry_Pi.Connect import Connect
from Settings import BT_PORT_NAME
from Datastorage.Processing import Processing
from Datastorage.storage import Storage
from Datastorage.dateConverter import Converter

if __name__ == '__main__':
    '''
    Setup
    '''
    stg = Storage()

    cnt = Connect(BT_PORT_NAME)
    cnt.start()

    date_cv = Converter()

    program_running = True
    while program_running:
        # if there is  new data, we store it, and translate it to the correct date
        if cnt.data_available():
            stg.store_data(cnt.get_new_data())

            if stg.is_date():
                date_cv.update_date(stg.get_raw_date())

            if stg.button_pressed():
                print(stg.get_temp("Driel boven", date_cv.get_date()))



    cnt.stop()
    sys.exit()

