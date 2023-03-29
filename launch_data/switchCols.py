import pandas as pd

DF = pd.read_csv("launch_data/12_03_2023/march_launch2.csv", usecols=range(0, 22)) #change cols for the new datas
newcol = DF["timestamp"].subtract(DF["timestamp"][0]).div(1000)
DF.insert(loc=0, column="timeSeconds", value=newcol)
#print(DF)
DF.to_csv("launch_data/Simulink_format/march_launch_2_SF.csv", index=False) #SF = simulink format