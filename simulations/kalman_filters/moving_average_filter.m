%CSV Data
D = csvread("11_16_good_move_data.csv");

%Eventual output (N rows, 2 columns
X = zeros(length(D), 2);

%Split data into lat/long
lat = D(:,1);
lon = D(:,2);

%Set up a queue of 5 most recent data points
lat_queue = lat(1:5);
lon_queue = lon(1:5);

%Add first warmup points to the output
X(1:5, 1) = lat_queue;
X(1:5, 2) = lon_queue;

%Iterate through and apply the moving average to the data
for i = 6:length(D)
    %Add current elements to the lat and lon queues
    lat_queue(mod(i, 5) + 1) = lat(i);
    lon_queue(mod(i, 5) + 1) = lon(i);
    
    %Sum the latitude
    lat_total = sum(lat_queue);
    lon_total = sum(lon_queue);
    
    %Calculate the average latitude
    cur_lat = lat_total / 5;
    cur_lon = lon_total / 5;
    
    %Add the lat and long to the output
    X(i,1) = cur_lat;
    X(i,2) = cur_lon;
end

%Output to CSV and preserve precision
dlmwrite('moving_avg_output.csv', X, 'delimiter', ',', 'precision', 13);