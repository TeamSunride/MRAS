import pandas
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import kalmanFilterDesign as kf

matplotlib.use('TkAgg')
plt.style.use("ggplot")

df = pandas.read_csv("launch_data/20_11_2022/launch_1.csv", usecols=range(1, 20))
df["time_seconds"] = df["timestamp"].subtract(df["timestamp"][0]).div(1000)
print(df)

df.plot("time_seconds", y=["imuAX", "imuAY", "imuAZ"], xlabel="Time (s)", ylabel="Acceleration (m/s)",
        title="Acceleration")
plt.show()
"""

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

y_accel = df["imuAY"].to_numpy()
timestamps = df["timestamp"].to_numpy()
baroAlt = df["h"].to_numpy()
time_seconds = df["time_seconds"].to_numpy()
timedelta_seconds = (timestamps[1] - timestamps[0]) / 1000

#print(y_accel.shape)
estimatedAlt = np.zeros(y_accel.shape)

estimate = kf.KalmanFilter()
for i in range(0, len(y_accel)):
        state = estimate.prediction(y_accel[i])
        estimate.update(baroAlt[i]) 
        estimatedAlt[i] = state[0][0]
print(estimatedAlt.shape)
print(baroAlt.shape)
fig, ax = plt.subplots(constrained_layout=True)
ax.plot(time_seconds, baroAlt, label="barometric alt")
ax.plot(time_seconds, estimatedAlt, label="estimated alt")
ax.plot(time_seconds, y_accel, label="acceleration")
#plt.plot(time_seconds, [baroAlt, estimatedAlt], label="Estimated Altitude (m)")
plt.show()


