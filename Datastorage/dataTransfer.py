import pandas as pd
import time
import os

total_temp = pd.DataFrame(columns=['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'Average Temperatuur'])
total_water = pd.DataFrame(columns=['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'Average Waterhoogte'])
text_list = []


def csv_to_dataframe(file_path):
    start_time = time.time()
    df = pd.read_csv(file_path, sep=';')
    df = remove_wrong_data(df)
    data = df[
        ['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'GROOTHEID_OMSCHRIJVING', 'NUMERIEKEWAARDE']]
    end_time = (time.time() - start_time)
    print('Scan completed within ' + str(end_time) + " seconds")
    return data


def remove_wrong_data(data_frame):
    print('Clean up data')
    new_df = data_frame[pd.to_numeric(data_frame['NUMERIEKEWAARDE'], errors='coerce').notnull()].copy()
    new_df['NUMERIEKEWAARDE'] = new_df['NUMERIEKEWAARDE'].apply(pd.to_numeric)
    new_df = new_df[new_df.NUMERIEKEWAARDE <= 10000]
    return new_df


def calc_average(data_frame):
    print('Calculating Average')
    column_type = "Average " + data_frame.iloc[0]['GROOTHEID_OMSCHRIJVING']
    data = data_frame.copy().groupby(['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM'])[
        'NUMERIEKEWAARDE'].mean().reset_index()
    data.rename(columns={'NUMERIEKEWAARDE': column_type}, inplace=True)
    return data


def add_to_total_data_Frame(final_df):
    print('Adding to total frame')
    global total_water, total_temp
    if final_df.columns[-1] == 'Average Waterhoogte':
        total_water = total_water.append(final_df)
    else:
        total_temp = total_temp.append(final_df)


# Convert csv to dataframes
base_path = '/Users/stijnbrugman/Documents/GitHub/Mod8_project/Datastorage/Data/'
for dict1 in os.listdir(base_path):
    new_base_path = base_path + dict1 + "/"
    if dict1 == '.DS_Store':
        continue
    for dict2 in os.listdir(new_base_path):
        last_base_path = new_base_path + dict2 + "/"
        for file in os.listdir(last_base_path):
            print('------------- Start new file -------------')

            file_path = last_base_path + file
            data_frame = csv_to_dataframe(file_path)
            df = calc_average(data_frame)
            add_to_total_data_Frame(df)

            print('------------- File Completed ------------- \n')

# Convert to csv again
total_water.to_csv('/Users/stijnbrugman/Documents/GitHub/Mod8_project/Datastorage/Output/water.csv', index=False)
total_temp.to_csv('/Users/stijnbrugman/Documents/GitHub/Mod8_project/Datastorage/Output/temp.csv', index=False)
