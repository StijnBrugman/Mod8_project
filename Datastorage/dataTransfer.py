import pandas as pd
import time

text_list = []

start_time = time.time()
with open('Data/20210531_011.csv', "r") as my_input_file:
    first_line = my_input_file.readline().split(';')
    df = pd.DataFrame(columns = first_line)
    for index, line in enumerate(my_input_file):
        if index > 1000: break
        line = line.split(";")
        df.loc[len(df)] = line
data = df[['MEETPUNT_IDENTIFICATIE','LOCATIE_CODE','GROOTHEID_OMSCHRIJVING','WAARNEMINGDATUM','REFERENTIE','NUMERIEKEWAARDE']]
print(time.time()-start_time)
data.to_csv('/Users/stijnbrugman/Documents/GitHub/Mod8_project/Datastorage/Data/new_df.csv',index = False, header=True)
print(df)