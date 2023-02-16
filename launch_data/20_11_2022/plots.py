import pandas
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
plt.style.use("ggplot")

df = pandas.read_csv("launch_data/20_11_2022/launch_1.csv", usecols=range(1, 20))
df["time_seconds"] = df["timestamp"].subtract(df["timestamp"][0]).div(1000)
#print(df)

"""
df.plot("time_seconds", y=["imuAX", "imuAY", "imuAZ"], xlabel="Time (s)", ylabel="Acceleration (m/s)",
        title="Acceleration")
plt.show()

df.plot("time_seconds", y=["imuGX", "imuGY", "imuGZ"], xlabel="Time (s)", ylabel="Gyroscope (unit?)",
        title="Gyroscope Data")
plt.show()

df.plot("time_seconds", y=["imuMX", "imuMY", "imuMZ"], xlabel="Time (s)", ylabel="Magnetometer value",
        title="Magnetometer Data")
plt.show()

df.plot("time_seconds", y=["pressure"], xlabel="Time (s)", ylabel="Pressure (Pa)",
        title="Barometer data")
plt.show()

df["h_adjusted"] = df["h"] - df["h"][0]
df.plot("time_seconds", y=["h_adjusted"], xlabel="Time (s)", ylabel="Altitude (m)",
        title="Barometric altitude (adjusted)")
plt.show()
"""

df.plot("time_seconds", y=["h"], xlabel="Time (s)", ylabel="Altitude (m)",
        title="Barometric altitude")
plt.show()

