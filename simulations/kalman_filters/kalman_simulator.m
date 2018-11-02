% CONSTANTS %
N = 4;   %number of inputs
q = 0.1; %error in sensor data
r = 0.5; %confidence in the model

% Initialize Constant Matrices
Q = q*eye(N);   %Error matrix
R = r*eye(N);   %Confidence matrix ("key for sensor fusion")

% State variables
x = [35.210586, 0, -97.442081, 0];
P = r*eye(N);
S = P;

%Plotting variables
X = [];

%Run the filter on a dataset
while true
    %Predict the future
    [x, P] = predict(x, P);
    
    %Update based on what actually happened
    [x, P, S] = update(x, P, y, S);
    
    
end

%Plot the results



% HELPER FUNCTIONS %
function [x, P] = predict(x, P)
    A = eye(N); %Function of the motion model state
    
    %Predict the next state given the previous state
    x = A*x;
    
    %Predict the next covariance given the previous values
    P = A * P * transpose(A);
end

function [x, P, S] = update(x, P, y, S_old)
    H = eye(N); %Function of the measurement model state
    
    %Calculate the innovation
    v = y - (H * x);
    
    %Predict the measurement covariance
    S = (H * P * transpose(H)) + R;
    
    %Calculate Kalman gain
    K = P * transpose(H) * S_old;
    
    %Calculate the updated state
    x = x + (K * v);
    
    %Calculate the current uncertainty in the model
    P = P - (K * S * transpose(K));
end