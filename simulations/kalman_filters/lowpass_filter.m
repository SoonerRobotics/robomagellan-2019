%CSV Data
D = csvread("11_16_good_move_data.csv");

%Eventual output (N rows, 2 columns
X = zeros(length(D), 2);

%Split data into lat/long
lat = D(:,1);
lon = D(:,2);

%Add first warmup points to the output
X(1, 1) = lat(1);
X(1, 2) = lon(1);

K = .05;

%Iterate through and apply the moving average to the data
for i = 2:length(D)
    
    %Add the lat and long to the output
    X(i,1) = (1-K)*X(i-1,1) + K*lat(i);
    X(i,2) = (1-K)*X(i-1,2) + K*lon(i);
end

%Output to CSV and preserve precision
dlmwrite('lowpass_filter_output.csv', X, 'delimiter', ',', 'precision', 13);

subplot(2,1,1);
plot(D(:,1), D(:,2))
subplot(2,1,2);
plot(X(:,1), X(:,2))