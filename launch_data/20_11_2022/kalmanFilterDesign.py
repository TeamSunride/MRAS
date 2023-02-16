import numpy as np
import pandas as pd

## DIVERGES CHECK FOR ERRORS
class KalmanFilter:
    def __init__(self):
        pass


    isInitialised = 0

    ## Constants
    g = -9.81   #m/s^2
    delta_t = 10 #s
    accelSTD = 0.1 #acceleration standard deviation
    
    # state
    state = np.array(([0],[0]), dtype=np.float64) # pos & velocity in z axis (up) at time 'n'
    stateTransitionMat = np.array(([1, delta_t], [0, 1]), dtype=np.float64) # since pos = vel + accel*t
    controlMat = np.array(([0.5*(delta_t**2)],[delta_t]), dtype=np.float64) # since accel = pos/t^2 & accel = vel/t
    controlInput = np.array([0], dtype=np.float64) # accel input

    covarianceMat = np.array(([5 ,0],[0, 5]), dtype=np.float64) # high starting variance
    processNoiseMat = np.array(([(delta_t**4)/4, (delta_t**3)/3], [(delta_t**3)/2, delta_t**2]), dtype=np.float64) * accelSTD**2

    observationMat = np.array(([1, 0]), dtype=np.float64)
    #print(observationMat[:, np.newaxis])
    #print(np.transpose(observationMat))
    measCovarianceMat = np.array(([20]), dtype=np.float64)  #assuming altimeter STD 20m
    meas = np.array([0], dtype=np.float64) #assuming initial alt 0
   # @classmethod
    def prediction(self, acceleration):

        #if self.isInitialised != 1:
        #state prediction
        self.controlInput[0] = acceleration
        self.state = np.matmul(self.stateTransitionMat, self.state) + np.matmul(self.controlMat, self.controlInput)
        self.covarianceMat = np.matmul(self.stateTransitionMat, self.covarianceMat) @ np.transpose(self.stateTransitionMat) + self.processNoiseMat
        #print(self.covarianceMat)
        return self.state[0][0]

    def update(self, barometricAlt):
        #innovationMat = 
        self.meas[0] = barometricAlt
        observationTranspose = self.observationMat[:, np.newaxis]
        innovationCovarianceMat = np.matmul(self.observationMat, self.covarianceMat) @ observationTranspose + self.measCovarianceMat

        kalmanGainMat = np.matmul(self.covarianceMat, observationTranspose) @ innovationCovarianceMat
        self.state = self.state + np.matmul(kalmanGainMat, (self.meas - np.matmul(self.observationMat, self.state)))
        self.covarianceMat = np.matmul((np.identity(2) - np.matmul(kalmanGainMat, self.observationMat)), self.covarianceMat)

if __name__ == "__main__":

    #print(a @ b)
    df = pd.read_csv("launch_data/20_11_2022/launch_1.csv", usecols=range(1, 20))
    df = df[df["timestamp"] < df["timestamp"][0] + 1000 * 10]

    y_accel = df["imuAY"].to_numpy()
    timestamps = df["timestamp"].to_numpy()
    baroAlt = df["h"].to_numpy()
    timedelta_seconds = (timestamps[1] - timestamps[0]) / 1000

    estimate = KalmanFilter()

    estimate.delta_t = timedelta_seconds

    for i in range(0, len(y_accel)):
        print(estimate.prediction(y_accel[i]))
        estimate.update(baroAlt[i]) 




