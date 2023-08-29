% Created by Nikilesh

% Used kalmanfilter.net 


function [alt, vel, state, covarianceMatrix] = LinearKalmanFilter(accel, baroAlt, state, covarianceMatrix, dt, STDacc)
%predicts the next state of the system
    g= 9.81;
    delta_t = dt;
    accelSTD = STDacc;
    
    % Transition [1 delta]       Contol [0.5*delta^2]
    %            [0     1]              [    delta  ]

    stateTransitionMatrix = [1 delta_t; 0 1];
    controlMatrix = [0.5*(delta_t^2) delta_t]';
    controlInput = (accel-g);
    % Process Noise [ t^4/4  t^3/2]     
    %               [ t^2/2  t    ]
    processNoise = [delta_t^4/4 delta_t^3/2; delta_t^2/2 delta_t^2] * accelSTD^2;
    observationMatrix = [1 0];
    measCovariance = 80.67;

    meas = baroAlt;
   
    alt = state(1,1);
    vel = state(2,1);

    innovationCovarianceMatrix = observationMatrix * covarianceMatrix * observationMatrix' + measCovariance;

    kalmanGain = covarianceMatrix * observationMatrix' / innovationCovarianceMatrix;
    state = state + kalmanGain * (meas - observationMatrix * state);
    covarianceMatrix = (eye(2) - kalmanGain * observationMatrix) * covarianceMatrix * (eye(2) - kalmanGain * observationMatrix)' + kalmanGain * measCovariance * kalmanGain';

    state = stateTransitionMatrix * state + controlMatrix * controlInput;
    covarianceMatrix = stateTransitionMatrix * covarianceMatrix * stateTransitionMatrix' + processNoise;  
end
