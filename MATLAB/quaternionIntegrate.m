% Created by Nikilesh. 23/08/23
% 
% Quaternion Integration function, quaternions are in hamilton convention
% and all the angles should be radians. Source: Quaternion kinematics for
% the error-state KF, Section 4.6. Arxiv Link: https://arxiv.org/pdf/1711.02508.pdf 

function q_np1 = quaternionIntegrate(q_n,w_n,w_np1,dt)

    w_bar = (w_n + w_np1)./2;
    ang = norm(w_bar)*dt/2;
    
    q_wdt = [cos(ang), w_bar.*(sin(ang)/norm(w_bar))];
    %q_wdt = q_wdt ./ norm(q_wdt);
    w_cross = cross(w_n , w_np1);
    sum_eq227 = q_wdt + (dt^2 / 24).* [0, w_cross];
    %sum_eq227 = sum_eq227 ./ norm(sum_eq227);
    
    q_np1 = quatmultiply(q_n,sum_eq227);
    q_np1 = q_np1 ./ norm(q_np1);

end