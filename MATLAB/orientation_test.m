%% Load data

mat = load("orientation_test_data/data.mat");
data = mat.p;
[Nrows,Ncols] = size(data);
q_mat = zeros(Nrows,4);
%% Quaternion integration
delta_t = 0.001;
w_0 = data(1,:);    %assuming first quaternion is the normalized body rates
q_n = [0, w_0] ./ norm(w_0)   %make sure all quaternions are column vectors
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
