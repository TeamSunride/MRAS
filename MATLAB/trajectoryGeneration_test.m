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
alt = launch.data(:,21);

% to find velocity as it was wrong 
altEst = zeros(size(accelX));
velEst = zeros(size(accelX));
variance = 100;
state = [0 0]';
covarianceMatrix = [variance 0; 0 variance];
for i = 1:length(accelX)
    if i == 1
        [altEst(i), velEst(i), prevState, prevCovariance] = LinearKalmanFilter(accelY(i), alt(i), state, covarianceMatrix, 0.003, 28.16);
    else
        [altEst(i), velEst(i), prevState, prevCovariance] = LinearKalmanFilter(accelY(i), alt(i), prevState, prevCovariance, 0.001, 28.16);
    end
end

% apogee
[m,a_i] = max(alt);
altEst = altEst - altEst(1); % zeroing

% FOR CONVENIENCE 
% gyro = [gyroX(1:i), gyroY(1:i), gyroZ(1:i)] .* (pi/180);
% time = time(1:i); % change later
% altEst = altEst(1:i);

gyro = [gyroX, gyroY, gyroZ] .* (pi/180);
[Nrows, Ncols] = size(gyro);
accel = [accelX,accelY,accelZ];

%% Data processing 

% Low-pass on the acceleration data

w = 0.3; % weight: 1==no filter, 0==straight line
for i = 2:Nrows
    accel(i,:) = accel(i-1,:)*(1-w) + accel(i,:)*w;
end

%% Quaternion integration for orientation


orientation_quaternion = zeros(Nrows, 4);
orientation_euler = zeros(Nrows,3);
q_n = [0.7071, 0.7071, 0, 0];
orientation_quaternion(1,:) = q_n;

for i = 1:Nrows-1
    
    w_n = gyro(i,:);
    w_np1 = gyro(i+1,:);
    dt = time(i+1) - time(i);
    q_np1 = quaternionIntegrate(q_n, w_n, w_np1, dt);
    orientation_quaternion(i+1,:) = q_np1;
    q_n = q_np1;

end
[r, p, y] = quat2angle(orientation_quaternion, "ZYX");
%% Position -- how?

% ideas: 1. use the estimated altitude and orientation to guess the x,y,z
%        2. double integrate accelerometer data (BAD DATA QUALITY)


RotationMatrix = quat2rotm(orientation_quaternion); % 3x3xDatapoints, 3 dimensional tensor
aligned_accel = zeros(size(accel));
for i = 1:Nrows
    aligned_accel(i,:) = (RotationMatrix(:,:,i)*accel(i,:)')';
end

% METHOD #2
% using forward euler integration for now
pos = zeros(size(aligned_accel)); 
pos(1,1) = 0; % x axis translation
pos(1,2) = 0; % y axis 
pos(1,3) = 0; % z axis 

vel = zeros(size(aligned_accel));
vel(1,:) = [0,0,0];

for i = 2:Nrows
    vel(i,:) = vel(i-1,:) + aligned_accel(i,:).*(time(i)-time(i-1));
    vel(i,3) = velEst(i);
    pos(i,:) = pos(i-1,:) + vel(i,:).*(time(i)-time(i-1));
end 

% METHOD #1
pos_projecting = zeros(size(aligned_accel)); 


B = p; % beta for pitch
A = y; % alpha for yaw
rotM_2axis = zeros(3,3,Nrows);
for i = 1:length(B)

% doest work 
% rotM_pitch = [cos(B(i)), 0, sin(B(i)); 
%               0,     1,     0;
%               -sin(B(i)),0, cos(B(i))];
% rotM_yaw = [cos(A(i)), -sin(A(i)), 0;
%             sin(A(i)), cos(A(i)), 0;
%             0,      0,      1];
% rotM_2axis(:,:,i) = rotM_yaw*rotM_pitch; % don't know if it will work or even correct

pos_projecting(i,:) = [0,cos(A(i))*cos(B(i))*altEst(i), altEst(i)]; %wrong
end
%% Data Visualization 

% figure(1)
% plot(time, r)
% legend("pitch or yaw??")
% figure(2)
% plot(time,p)
% legend("roll")
% figure(3)
% plot(time,y)
% legend("pitch or yaw??")


figure(5)
%plot(time,gyro)
for i = 18000:20:Nrows-1 %% looping faster as it was slow

qs = quaternion(orientation_quaternion(i,:));
qf = quaternion(orientation_quaternion(i+1,:));
position = [0,0,0];
subplot(1,2,1);
patch = poseplot(qs,position,"ENU");
xlabel("North-x (m)")
ylabel("East-y (m)")
zlabel("Up-z (m)");


q = slerp(qs,qf,1);
set(patch, Orientation=q, Position=position)
drawnow

subplot(1,2,2);
plot(time(18000:i),altEst(18000:i));
drawnow

end
