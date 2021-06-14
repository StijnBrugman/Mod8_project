import sys
from Rasberry_Pi.Connect import Connect
from Settings import BT_PORT_NAME
from Datastorage.Processing import Processing
from Datastorage.storage import Storage

if __name__ == '__main__':
    '''
    Setup
    '''
    #prs = Processing()
    # prs.start()

    stg = Storage()

    cnt = Connect(BT_PORT_NAME)
    cnt.start()

    program_running = True
    while program_running:
        # if there is  new data, we store it
        if cnt.data_available():
            stg.store_data(cnt.get_new_data())

    cnt.stop()
    sys.exit()

