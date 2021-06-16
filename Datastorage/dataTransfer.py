"""
File for transforming csv-input data into date-average csv-output data

pandas is used to temporary store the data base,

after all the incorrect data is removed
and the average are calculated, the
data-frames are put in the correct 'total'-list

note: Program should run up to 1 second per file
and panda should be installed. IF NOT:

###REQUIRED###
>> Pip install pandas <<

"""

# Importing modules
import pandas as pd
import time
import os

# Place holders for final total-lists
total_temp = pd.DataFrame(columns=['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'Average Temperatuur'])
total_water = pd.DataFrame(columns=['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'Average Waterhoogte'])

# Conversion from csv to data-frame
def csv_to_dataframe(file_path):
    # Split the file based on ';'
    start_time = time.time()
    df = pd.read_csv(file_path, sep=';')

    # remove incorrect data from Data-Frame
    df = remove_wrong_data(df)

    # Get the necessary columns
    data = df[ ['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM', 'GROOTHEID_OMSCHRIJVING', 'NUMERIEKEWAARDE']]
    end_time = (time.time() - start_time)
    print('Scan completed within ' + str(end_time) + " seconds")
    return data

# Remove rows with wrongful data
def remove_wrong_data(data_frame):
    print('Clean up data')

    # Deleting Nan-values
    new_df = data_frame[pd.to_numeric(data_frame['NUMERIEKEWAARDE'], errors='coerce').notnull()].copy()
    new_df['NUMERIEKEWAARDE'] = new_df['NUMERIEKEWAARDE'].apply(pd.to_numeric)

    # Delete to high values
    new_df = new_df[abs(new_df.NUMERIEKEWAARDE) <= 10000]
    return new_df

# Calculating average value per year and location
def calc_average(data_frame):
    print('Calculating Average')

    # Check data-type 'Temperature || Waterheight'
    column_type = "Average " + data_frame.iloc[0]['GROOTHEID_OMSCHRIJVING']

    # Calculate mean per location and year
    data = data_frame.copy().groupby(['MEETPUNT_IDENTIFICATIE', 'LOCATIE_CODE', 'WAARNEMINGDATUM'])[
        'NUMERIEKEWAARDE'].mean().reset_index()
    data.rename(columns={'NUMERIEKEWAARDE': column_type}, inplace=True)
    return data

# Adding file to the 'correct' total-list
def add_to_total_data_Frame(final_df):
    print('Adding to total frame')

    # Reference to global total-lists
    global total_water, total_temp

    # Checking which total-list it should go to
    if final_df.columns[-1] == 'Average Waterhoogte':
        total_water = total_water.append(final_df)
    else:
        total_temp = total_temp.append(final_df)


# Convert csv to dataframes
base_path = '../Datastorage/Data/'

# Go trough all the files in Data
for dict1 in os.listdir(base_path):
    new_base_path = base_path + dict1 + "/"

    # Don't try -DS_Store directory
    if dict1 == '.DS_Store':
        continue

    for dict2 in os.listdir(new_base_path):
        last_base_path = new_base_path + dict2 + "/"
        for file in os.listdir(last_base_path):
            print('------------- Start new file -------------')

            # Init path
            file_path = last_base_path + file

            # converting and removing non-required data
            data_frame = csv_to_dataframe(file_path)

            # Calc average
            data_frame = calc_average(data_frame)

            # Adding total-list
            add_to_total_data_Frame(data_frame)

            print('------------- File Completed ------------- \n')

# Convert to csv again
total_water.to_csv('../Datastorage/Output/water.csv', index=False)
total_temp.to_csv('../Datastorage/Output/temp.csv', index=False)
