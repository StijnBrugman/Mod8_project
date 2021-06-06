import pandas as pd
import numpy as np


class Storage:

    def __init__(self):
        self.data_frame = self.init_data_frame()
        print(self.data_frame)

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
        water_level = self.data_frame[conditions]['Average Waterhoogte'].iloc[0]
        return water_level

    def get_temp(self, place, date):
        conditions = self.get_conditions(place, date)
        temp_level = self.data_frame[conditions]['Average Temperatuur'].iloc[0]
        return temp_level

    def get_conditions(self, place, date):
        conditions = (
                (self.data_frame['MEETPUNT_IDENTIFICATIE'] == place) &
                (self.data_frame['WAARNEMINGDATUM'] == date)
        )
        return conditions
