/*
 * Sierra College Computer Engineering Club: Sparkfun AVC
 * Navigation Subsystem
 * Authors: Kristoffer Semelka
 */
#include "common.h"
#include "nav.h"
#include "sensors.h"
#include <stdlib.h>
#include <math.h>

/*
  We'll need math and stdlib... someday.
  TODO: What standard libraries are available
  on the TI?
*/

motionData MotionData;

void initNav()
{
  /*
    Nothing goes here yet.
    For future milestones, include Bezier curve data here.
  */
}

float findCorrection(float current, float desired)
{
  /*
    Takes the current heading and desired heading, and
    finds the (shortest) difference between the two.
  */
  float tempAngle, correction;
  
  tempAngle = desired - current;

  if ( abs(tempAngle) > 180)
    {
      /*
       Use the other angle, in the other direction
     */

      if ( tempAngle > 0)
        {
          correction = (360.0f - tempAngle) * -1;
        }
      else
        {
          correction = (-360.0f - tempAngle) * -1;
        }
    }

  else
    { correction = tempAngle; }
  
  return correction;
}

float pidAdjust(float headingDiff)
{
  /*
    Takes a value and applies the PID controller to it.
    Currently only does a proportional correction.
  */
  float newHeading;
  float kp;

  kp = .7f;

  /*
    Maybe this is a good value. Maybe it's not! Who knows!
  */

  newHeading = headingDiff * kp;

  return newHeading;
}

void updateNav()
{
  /*
    This function:
     - gets the navigation data from sensors;
     - "gets" (constant for now) desired heading;
     - finds difference;
     - applies PID (just P for now);
     - creates instructions for motion module;
     - and pushes instructions to MotionData
     on every update.
  */
  navData* NavData;
  float desiredHeading;
  float headingDiff;
  float adjustedCorrection;
  
  NavData = getNavData();
  desiredHeading = M1HEADING;

  headingDiff = findCorrection(NavData->heading, M1HEADING);

  adjustedCorrection = pidAdjust(headingDiff);
  
  MotionData.heading = adjustedCorrection;
  
}

motionData* getMotionData()
{
  return &MotionData;
}
