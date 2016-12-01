#include "bico.h"
#define MAX_FOLLOW_DISTANCE 100
#define MAX_WALL_DISTANCE 600
#define DEFAULT_SPEED 50
#define TURN_SPEED 15

motor_cfg_t M1, M2;

void _start() {
    M1.id = 0;
    M2.id = 1;
    search_wall();
    follow_wall();
}

void search_wall() {
    unsigned int distances[16];
    move_forward();                         // Initializes the movement.
    read_sonars(3, 4, distances);

    while(front_is_clear(distances, MAX_WALL_DISTANCE)) {
        read_sonars(3, 4, distances);
    }

    stop();                                 // Stops when the robot's front is blocked
    turn_right();

    return;
}

void follow_wall() {
    // Turns the robot left in case the wall is too far away.
    register_proximity_callback(0, MAX_FOLLOW_DISTANCE, adjust_left);

    while(1) {
        // Goes forward and turns if the front side of the robot is blocked.
        move_forward();
        while(front_is_clear(distances, MAX_FOLLOW_DISTANCE)) {
            read_sonars(3, 4, distances);
        }
        stop();
        turn_right();
    }
}

void turn_right() {
    M1.speed = 0;                          // Rotates the robot to the right.
    M2.speed = TURN_SPEED;
    set_motors_speed(&M1, &M2);

    while(front_is_clear(distances, MAX_WALL_DISTANCE)) {
        read_sonars(3, 4, distances);
    }

    stop();

    return;
}

void adjust_left() {
    M1.speed = TURN_SPEED;                  // Rotates the robot to the left.
    M2.speed = 0;
    set_motors_speed(&M1, &M2);
}

void stop() {
    M1.speed = 0;                           // Stops the robot.
    M2.speed = 0;
    set_motors_speed(&M1, &M2);
}

void move_forward() {
    M1.speed = DEFAULT_SPEED;               // Initialize the motors and sonars.
    M2.speed = DEFAULT_SPEED;
    set_motors_speed(&M1, &M2);
}

int front_is_clear(unsigned int distances[], int distance) {
    if(distances[2] < distance) && (distances[3] < distance)) {
        return 1;
    }

    return 0;
}
