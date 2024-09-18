#ifndef _DRAW_H_
#define _DRAW_H_

#include "calculate.h"
#include "move_funstion.h"

void arc(float cX, float cY, float endX, float endY, float dir) 
{ // (cX, cY, endX, endY, DIR)
  // get radius

  // Serial.println("  executing arc ");

  float dx = x1 - cX; // changed XCoordinate to x1

  float dy = y1 - cY; // changed YCoordinate to y1

  float radius = sqrt(dx * dx + dy * dy);

  // his homemade atan3 function
  // returns angle of dy/dx as a value from 0...2PI

  // find the sweep of the arc
  float angle1 = atan3(dy, dx);
  float angle2 = atan3(endY - cY, endX - cX);
  float sweep = angle2 - angle1;

  if (dir > 0 && sweep < 0) angle2 += 2 * PI;
  else if (dir < 0) angle1 += 2 * PI;

  sweep = angle2 - angle1;

  // find the length of the arc
  float len = abs(sweep) * radius;

  int i, num_segments = floor( len / .01 ); // calculate number segments

  // declare variables outside of loops because compilers can be really dumb and inefficient some times.
  float nx, ny, angle3, fraction;
  // float nz
  for (i = 0; i < num_segments; ++i) 
  {
    // some debug prints
    /*
      Serial.print ("num_segments = ");
      Serial.println (num_segments);
      Serial.print ("i= ");
      Serial.println (i);
    */
    // some debug prints

    // interpolate around the arc
    fraction = ((float)i) / ((float)num_segments);
    angle3 = ( sweep * fraction ) + angle1;

    // find the intermediate position
    nx = cX + cos(angle3) * radius;
    ny = cY + sin(angle3) * radius;
    calculateAngles(nx, ny, T);
    calcMoveSteps ();
    move2 (); // make a line to that intermediate position
  }

  // one last line hit the end
  R = endX;
  S = endY;
  strcpy (gCode, "G5"); // needed to terminate G2/G3 loop to arc();

  calculateAngles(endX, endY, T);
  calcMoveSteps();
  move2();
} // end void arc


void Bresenham(float x1, float y1, const float smallx2, const float smally2)// x2 and y2 were int const, algorithm Bresenham
{
  x1 = x1 * 100;   //increase accuracy with 2 digits
  y1 = y1 * 100;
  const float x2 = smallx2 * 100;
  const float y2 = smally2 * 100;

  int delta_x = (x2 - x1);
  // if x1 == x2, then it does not matter what we set here
  signed char const ix((delta_x > 0) - (delta_x < 0));
  delta_x = abs(delta_x) << 1;

  int delta_y = (y2 - y1);
  // if y1 == y2, then it does not matter what we set here
  signed char const iy((delta_y > 0) - (delta_y < 0));
  delta_y = abs(delta_y) << 1;

  move3(x1, y1);

  if (delta_x >= delta_y)
  {
    // error may go below zero
    int error = (delta_y - (delta_x >> 1));

    while (x1 != x2)
    {
      // reduce error, while taking into account the corner case of error == 0
      if ((error > 0) || (!error && (ix > 0)))
      {
        error -= delta_x;
        y1 += iy;
      }
      // else do nothing
      error += delta_y;
      x1 += ix;
      move3(x1, y1);
    }
  }

  else
  {
    // error may go below zero
    int error = (delta_x - (delta_y >> 1));
    while (y1 != y2)
    {
      // reduce error, while taking into account the corner case of error == 0
      if ((error > 0) || (!error && (iy > 0)))
      {
        error -= delta_y;
        x1 += ix;
      }
      // else do nothing
      error += delta_x;
      y1 += iy;
      move3(x1, y1);
    }
  }

  strcpy (gCode, "G5"); // needed to terminate G1 loop to Bresenham();

} // end void Bresenham


#endif // _DRAW_H_