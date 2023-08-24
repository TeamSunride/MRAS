% Created by Nikilesh Ramesh -- 24/08/2023

% Trajectory generation attempt #1 

% Current Idea: Use estimated altitude from linear kalman filter,
% orientation from quaternion integration (maybe try integrating
% magnetometer to this) and maybe gps (no data for gps yet) to build a trajectory

%% Load data
% Ideally run once

launch = load("launch_data_1.mat");

time = launch.data(:,1);

% RAW DATA
accelX = launch.data(:,2);
accelY = launch.data(:,3);
accelZ = launch.data(:,4);
gyroX = launch.data(:,8);
gyroY = launch.data(:,9);
gyroZ = launch.data(:,10);
magX = launch.data(:,11);
magY = launch.data(:,12);
magZ = launch.data(:,13);
pressure = launch.data(:,14);

gpsAlt = launch.data(:,18); % WRONG

% KALMAN FILTER OUTPUT
altEst = launch.data(:,21); 
velEst = launch.data(:,22); % SUSPECTED TO BE WRONG

% FOR CONVENIENCE 
gyro = [gyroX, gyroY, gyroZ] .* (pi/180);

%% Data processing 

% maybe some kind of filter to smooth data points 

%% Quaternion integration for orientation

[Nrows, Ncols] = size(gyro);
orientation_quaternion = zeros(Nrows, 4);
orientation_euler = zeros(Nrows,3);
q_n = [0.7071, 0.7071, 0, 0];
orientation_quaternion(1,:) = q_n;
%orientation_euler(1,:) = quat2angle(q_n);

for i = 1:Nrows-1
    
    w_n = gyro(i,:);
    w_np1 = gyro(i+1,:);
    dt = time(i+1) - time(i);
    q_np1 = quaternionIntegrate(q_n, w_n, w_np1, dt);
    orientation_quaternion(i+1,:) = q_np1;
    %orientation_euler(i+1,:) = quat2angle(q_np1);
    q_n = q_np1;

end

%% Data Visualization 
[p, q, r] = quat2angle(orientation_quaternion, "YXZ");
figure(1)
plot(time, [r,p,y])
legend("r","p","y")


%plot(time,gyro)
