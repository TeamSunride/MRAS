import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ["pressure", "altitude"]
df = pd.read_csv('altPressure.csv', names=headers)

df.set_index("pressure").plot()
plt.grid()
plt.show()