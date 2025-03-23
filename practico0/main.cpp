#include <iostream>
#include <vector.h>

Vector calculate_velocity(Vector initial_velocity, Vector acceleration, float delta_t)
{
    return initial_velocity + acceleration * delta_t;
}

Vector calculate_position(Vector initial_position, Vector initial_velocity, Vector acceleration, float delta_t)
{
    return initial_position + initial_velocity * delta_t + acceleration * delta_t * delta_t / 2;
}

int main()
{
    std::cout << "Insert initial velocity in x: ";
    float initial_velocity_x;
    std::cin >> initial_velocity_x;

    std::cout << "Insert initial velocity in y: ";
    float initial_velocity_y;
    std::cin >> initial_velocity_y;

    std::cout << "Insert initial velocity in z: ";
    float initial_velocity_z;
    std::cin >> initial_velocity_z;

    std::cout << "Insert delta t: ";
    float initial_delta_t;
    std::cin >> initial_delta_t;

    Vector initial_velocity(initial_velocity_x, initial_velocity_y, initial_velocity_z);
    std::cout << "Initial velocity: " << initial_velocity << std::endl;
    std::cout << "Delta t: " << initial_delta_t << std::endl;
    Vector acceleration(0, -9.8, 0);
    std::cout << "Acceleration: " << acceleration << std::endl;
    Vector initial_position(0, 0, 0);
    std::cout << "Initial position: " << initial_position << std::endl;

    float delta_t = initial_delta_t;

    Vector final_position = calculate_position(initial_position, initial_velocity, acceleration, initial_delta_t);

    while (final_position.getY() > 0)
    {
        std::cout << "Position in delta t = " << delta_t << ": " << final_position << std::endl;
        delta_t += initial_delta_t;
        final_position = calculate_position(initial_position, initial_velocity, acceleration, delta_t);
    }

    return 0;
}
