%% Load data

mat = load("orientation_test_data/data.mat");
data = mat.p;
[Nrows,Ncols] = size(data);
q_mat = zeros(Nrows,4);
%% Quaternion integration
delta_t = 0.005;
w_0 = data(1,:);    %assuming first quaternion is the normalized body rates
q_n = [1, 0, 0, 0]  ; %make sure all quaternions are column vectors
q_mat(1,:) = q_n;
for i = 1:(Nrows-1)
    
    w_n = data(i,:);
    w_np1 = data(i+1,:);
    w_bar = (w_np1 + w_n) / 2;

    ang = norm(w_bar)*delta_t / 2;
    q_wdt = [cos(ang), w_bar.*(sin(ang)/norm(ang))]; %might be a problem, may be not

    w_cross = cross(w_n , w_np1);
    sum_eq227 = q_wdt + (delta_t^2 / 24).* [0, w_cross];
    q_np1 = quatmultiply(q_n,sum_eq227);
    q_mat(i+1,:) = q_np1/norm(q_np1);
    q_n = q_np1/norm(q_np1);
end 

% GOES UNSTABLE : DONT KNOW WHY --- looks fixed after normalizing on line
% 24 and 25

%% Animation

for i = 1:Nrows-1

qs = quaternion(q_mat(i,:));
qf = quaternion(q_mat(i+1,:));
position = [0,0,0];
patch = poseplot(qs,position);
xlabel("North-x (m)")
ylabel("East-y (m)")
zlabel("Down-z (m)");

for coeff = 0:0.5:1
    q = slerp(qs,qf,coeff);
    set(patch, Orientation=q, Position=position)
    drawnow
end
end
%% Doest work
% position = [0,0,0];
% qs = quaternion(q_mat(1,:));
% patch = poseplot(qs,position);
% xlabel("North-x (m)")
% ylabel("East-y (m)")
% zlabel("Down-z (m)");
% for i = 1:Nrows-1
% 
%  qf = quaternion(q_mat(i+1,:));
% 
%  set(patch, Orientation=q, Position=position)
%  drawnow
%  pause(0.01)
% end