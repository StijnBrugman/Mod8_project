import pandas as pd
import numpy as np
from Settings import ENCODER_DC, DATA_DC
import time


class Storage:

    def __init__(self):
        self.data_frame = self.init_data_frame()
        self.encoder_dc = ENCODER_DC
        self.data_dc = DATA_DC
        self.date_check = False

        self.select_button = False

        self.distance = False

    def init_data_frame(self):
        '''
        Merge the Water & Temperature data_frame
        :return: data_frame
        '''

        # loading in data_files
        water = pd.read_csv("Datastorage/Output/water.csv")
        temperature = pd.read_csv("Datastorage/Output/temp.csv")

        # Merging data_frames
        merged_data_frame = pd.merge(water, temperature, how='left', on=['MEETPUNT_IDENTIFICATIE',
                                                                         'LOCATIE_CODE', 'WAARNEMINGDATUM'])
        merged_data_frame['WAARNEMINGDATUM'] = pd.to_datetime(merged_data_frame['WAARNEMINGDATUM'])
        merged_data_frame = merged_data_frame.sort_values(['MEETPUNT_IDENTIFICATIE', 'WAARNEMINGDATUM'],
                                                          ascending=(True, True))
        merged_data_frame.to_csv('Datastorage/Output/total.csv', index=False)

        return merged_data_frame

    def get_water(self, place, date):
        conditions = self.get_conditions(place, date)
        water_level = self.data_frame[conditions]['Average Waterhoogte']

        if water_level.size < 1:
            return None

        return water_level.iloc[0]

    def get_temp(self, place, date):
        conditions = self.get_conditions(place, date)
        temp_level = self.data_frame[conditions]['Average Temperatuur']

        if temp_level.size < 1:
            return None

        return temp_level.iloc[0]

    def get_conditions(self, place, date):
        conditions = (
                (self.data_frame['MEETPUNT_IDENTIFICATIE'] == place) &
                (self.data_frame['WAARNEMINGDATUM'] == date)
        )
        return conditions

    def store_data(self, raw_data):
        code, data = self.convert_raw_data(raw_data)

        try:
            code_equivalent = self.encoder_dc[code]
        except:
            print("Invalid Code")
            return


        self.date_check = self.date_checker(code_equivalent)
        self.select_button = self.button_check(code_equivalent)
        self.distance = self.distance_checker(code_equivalent)

        # Serial read shouldn't be stored, is just used as a check-up
        if code_equivalent == 'serial_sent':
            print("RECEIVING DATA", data)
        else:
            try:
                self.data_dc[code_equivalent] = int(data)
            except:
                print(code_equivalent, " doesn't contain any values")
                self.data_dc[code_equivalent] = 0

    def date_checker(self, code_equivalent):
        if code_equivalent in ['encoder_year', 'encoder_month', 'encoder_day']:
            return True
        return False

    def is_date(self):
        return self.date_check

    def distance_checker(self, code_equivalent):
        if code_equivalent in ['distance_A', 'distance_B', 'distance_C', 'distance_D', 'distance_E']:
            return True
        return False

    def is_distance(self):
        return self.distance

    def convert_raw_data(self, raw_data):
        return raw_data[0], raw_data[1:]

    def get_raw_date(self):
        correct_list = {'encoder_year', 'encoder_month', 'encoder_day'}
        date_dic = {key: val for key, val in self.data_dc.items() if key in correct_list}
        return date_dic

    def button_check(self, code_equivalent):
        if code_equivalent in ['encoder_button']:
            return True
        return False

    def button_pressed(self):
        return self.select_button

    def get_distance_data(self):
        correct_list = {'distance_A', 'distance_B', 'distance_C', 'distance_D', 'distance_E'}
        date_dic = {key: val for key, val in self.data_dc.items() if key in correct_list}
        return date_dic
