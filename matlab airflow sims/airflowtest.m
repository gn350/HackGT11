% Define the grid
x = linspace(-5, 5, 20); % X coordinates
y = linspace(-5, 5, 20); % Y coordinates
[X, Y] = meshgrid(x, y); % Create a mesh grid

% Define flow velocity
U = ones(size(X)); % X component of velocity
V = zeros(size(Y)); % Y component of velocity (no vertical flow)

% Plot the vector field
figure;
quiver(X, Y, U, V);
axis equal;
title('Basic Airflow Simulation');
xlabel('X-axis');
ylabel('Y-axis');

% Define the obstacle
obstacle = (X > 1) & (X < 2) & (Y > -1) & (Y < 1);
U(obstacle) = 0; % Block the flow
V(obstacle) = 0; % Block the flow

% Re-plot the vector field with the obstacle
figure;
quiver(X, Y, U, V);
hold on;
fill([1, 2, 2, 1], [-1, -1, 1, 1], 'k', 'FaceAlpha', 0.5); % Draw the obstacle
axis equal;
title('Airflow Simulation with Obstacle');
xlabel('X-axis');
ylabel('Y-axis');


% Simple animation loop
for t = 1:50
    % Update the velocity (example: oscillate)
    U = sin(0.1*t + X);
    V = cos(0.1*t + Y);
    
    % Update the plot
    clf;
    quiver(X, Y, U, V);
    hold on;
    fill([1, 2, 2, 1], [-1, -1, 1, 1], 'k', 'FaceAlpha', 0.5); % Obstacle
    axis equal;
    title('Airflow Simulation Animation');
    xlabel('X-axis');
    ylabel('Y-axis');
    pause(0.1); % Pause for animation effect
end
