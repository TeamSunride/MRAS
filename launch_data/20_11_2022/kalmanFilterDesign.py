# (i hate numpy)

import numpy as np
import pandas as pd


## DIVERGES CHECK FOR ERRORS
class KalmanFilter:
    def __init__(self):
        pass


    isInitialised = 0

    ## Constants
    g = -9.81   #m/s^2
    delta_t = 0.03 #s
    accelSTD = 28.1836 #acceleration standard deviation
    
    # state
    state = np.array(([0],[0]), dtype=np.float64) # pos & velocity in z axis (up) at time 'n'
    stateTransitionMat = np.array(([1, delta_t], [0, 1]), dtype=np.float64) # since pos = vel + accel*t
    controlMat = np.array(([0.5*(delta_t**2)],[delta_t]), dtype=np.float64) # since accel = pos/t^2 & accel = vel/t
    #print(controlMat)
    controlInput = np.array([0], dtype=np.float64) # accel input
    controlInput = controlInput.reshape(1,1)
    #print(controlInput.shape)

    covarianceMat = np.array(([500 ,0],[0, 500]), dtype=np.float64) # high starting variance
    processNoiseMat = np.array(([(delta_t**4)/4, (delta_t**3)/3], [(delta_t**3)/2, delta_t**2]), dtype=np.float64) * accelSTD**2

    observationMat = np.array(([1, 0]), dtype=np.float64)
    #print(observationMat[:, np.newaxis])
    #print(np.transpose(observationMat))
    measCovarianceMat = np.array([80.6726], dtype=np.float64)  #assuming altimeter STD 20m
   #s st print(measCovarianceMat.shape)
    meas = np.array([0], dtype=np.float64) #assuming initial alt 0
   # @classmethod
    def prediction(self, acceleration):

        #if self.isInitialised != 1:
        #state prediction
        self.controlInput[0] = acceleration + self.g
        #print(self.controlMat @ self.controlInput)
        #print(self.stateTransitionMat @ self.state)
        self.state = self.stateTransitionMat @ self.state + self.controlMat @ self.controlInput
        self.covarianceMat = np.matmul(self.stateTransitionMat, self.covarianceMat) @ np.transpose(self.stateTransitionMat) + self.processNoiseMat
        #print(self.covarianceMat)
        return self.state

    def update(self, barometricAlt):
        #innovationMat = 
        self.meas[0] = barometricAlt
        observationTranspose = self.observationMat[:, np.newaxis]
        innovationCovarianceMat = self.observationMat @ self.covarianceMat @ observationTranspose + self.measCovarianceMat
        #print(innovationCovarianceMat)
        #print("matrix")
        #print(self.covarianceMat)
        #print(innovationCovarianceMat)
        #print(np.array([1/innovationCovarianceMat[0]]))
       # print(observationTranspose)
        #print(np.array([1/innovationCovarianceMat[0]]).shape)
        kalmanGainMat = np.matmul(self.covarianceMat, observationTranspose) @ np.array([1/innovationCovarianceMat[0]])
        #print(kalmanGainMat)
        #print(kalmanGainMat[:, np.newaxis])
        kalmanGainMat = kalmanGainMat[:, np.newaxis]
        #print(kalmanGainMat)
        #print(self.observationMat)
        #print(self.state)
        #print((self.meas  - self.observationMat @ self.state).shape)
        #print(self.meas)
        self.state = self.state + kalmanGainMat @ (self.meas  - self.observationMat @ self.state).reshape(1,1)
        #print(self.state)
        #print(kalmanGainMat)
        #print(self.measCovarianceMat)
        #print(self.observationMat)
        #print(np.identity(2) - kalmanGainMat @ self.observationMat.reshape(1,2))
        #print(kalmanGainMat)
        #print(self.measCovarianceMat)
        #print(np.transpose(kalmanGainMat))
        #print(kalmanGainMat @ self.measCovarianceMat.reshape(1,1) @ np.transpose(kalmanGainMat))
        self.covarianceMat = (np.identity(2) - kalmanGainMat @ self.observationMat.reshape(1,2)) @ self.covarianceMat @ np.transpose(np.identity(2) - kalmanGainMat @ self.observationMat.reshape(1,2)) + kalmanGainMat @ self.measCovarianceMat.reshape(1,1) @ np.transpose(kalmanGainMat)

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

    #print(estimate.delta_t)
    for i in range(0, len(y_accel)):
        state = estimate.prediction(y_accel[i])
        estimate.update(baroAlt[i]) 
        #print(state)






