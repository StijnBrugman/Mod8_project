from Datastorage.storage import Storage

if __name__ == '__main__':
    '''
    Setup
    '''

    stg = Storage()
    print(stg.get_temp("Borgharen dorp","01/01/2019"))
    print(stg.get_water("Borgharen dorp", "01/01/2019"))