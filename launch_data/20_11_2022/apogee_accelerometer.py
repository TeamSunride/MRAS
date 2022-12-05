import pandas
import numpy as np
import matplotlib.pyplot as plt

df = pandas.read_csv("launch_1.csv", usecols=range(1, 20))

# trim the dataframe for the desired time
df = df[df["timestamp"] < df["timestamp"][0] + 1000 * 10]

y_accel = df["imuAY"].to_numpy()
timestamps = df["timestamp"].to_numpy()

velocity = np.zeros(y_accel.shape)
position = np.zeros(y_accel.shape)

for i in range(1, y_accel.shape[0]):
    timedelta_seconds = (timestamps[i] - timestamps[i-1]) / 1000
    accel = y_accel[i] - 9.81
    velocity[i] = velocity[i-1] + accel * timedelta_seconds
    position[i] = position[i-1] + velocity[i] * timedelta_seconds

apogee = np.amax(position)
apogee_time = timestamps[np.argmax(position)]

print(f"Apogee: {apogee} Apogee time: {apogee_time}")

df["h_adjusted"] = df["h"] - df["h"][0]

plt.plot(timestamps, velocity, label="Velocity")
plt.plot(timestamps, position, label="Position")
plt.plot(timestamps, y_accel, label="Y Acceleration")
plt.plot(apogee_time, apogee, "*", label="Apogee")
plt.plot(timestamps, df["h_adjusted"], label="Barometric height")
plt.legend()
plt.show()

