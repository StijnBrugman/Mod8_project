
from Rasberry_Pi.Connect import Connect
from Settings import BT_PORT_NAME
from Datastorage.Processing import Processing

if __name__ == '__main__':
    '''
    Setup
    '''
    prs = Processing()
    prs.start()

    cnt = Connect(BT_PORT_NAME)
    cnt.start()