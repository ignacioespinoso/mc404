#include "api_robot.h" /* Robot control API */

void rotaciona_robo();

/* main function */
void _start(void) {
  unsigned int distances[16];
  unsigned int s1, s2;

  do {
    s1 = read_sonar(3);
    s2 = read_sonar(4);

    /* Rotates the robot if the front side is blocked*/
    if((s1 < 1200) || (s2 < 1200)) {
        set_speed_motors(0,0); /*Stops the robot first*/
        rotaciona_robo();
    }

    set_speed_motors(50, 50);
  } while (1);
}

/* Rotates robot while it has something in the front. */
void rotaciona_robo() {
  unsigned int s1, s2, s3, s4, s5;

  /*Sets the initial values to the sonars*/
  s1 = read_sonar(3);
  s2 = read_sonar(4);
  s3 = read_sonar(5);
  s4 = read_sonar(6);
  s5 = read_sonar(7);

  /*Turns right if possible*/
  if((s3 > 600) && (s4 > 600) && (s5 > 600)) {
    set_speed_motors(0, 5);
  /* If not, turns left*/
  } else {
    set_speed_motors(5, 0);
  }

  while((s1 < 1200) || (s2 < 1200)) {
      s1 = read_sonar(3);
      s2 = read_sonar(4);
  }

  /* Stops the movement if the robot is free to move forward*/
  set_speed_motors(0, 0);

  return;
}
