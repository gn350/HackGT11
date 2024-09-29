% Define the grid
[X, Y, Z] = meshgrid(linspace(-5, 5, 10), ...
                     linspace(-5, 5, 10), ...
                     linspace(-5, 5, 10)); % Create a mesh grid

% Define flow velocity components
U = ones(size(X));  % X component
V = zeros(size(Y)); % Y component
W = zeros(size(Z)); % Z component

% Plot the vector field
figure;
quiver3(X, Y, Z, U, V, W, 'r'); % Red vectors
axis equal;
title('Basic 3D Airflow Simulation');
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
grid on;

% Define an obstacle
obstacleX = [-1, 1, 1, -1, -1];
obstacleY = [-1, -1, 1, 1, -1];
obstacleZ = [1, 1, 1, 1, 1]; % A flat obstacle at Z=1

% Plot the obstacle
hold on;
fill3(obstacleX, obstacleY, obstacleZ, 'k', 'FaceAlpha', 0.5); % Draw the obstacle

% Simple animation loop
for t = 1:50
    % Update the velocity (example: oscillate)
    U = sin(0.1*t + X);
    V = cos(0.1*t + Y);
    W = 0.5 * sin(0.1*t + Z);

    % Update the plot
    clf;
    quiver3(X, Y, Z, U, V, W, 'r');
    hold on;
    fill3(obstacleX, obstacleY, obstacleZ, 'k', 'FaceAlpha', 0.5);
    axis equal;
    title('3D Airflow Simulation Animation');
    xlabel('X-axis');
    ylabel('Y-axis');
    zlabel('Z-axis');
    grid on;
    pause(0.1); % Pause for animation effect
end
