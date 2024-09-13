/*
The 'recvWithStartEndMarkers()' function receives data from the serial port and only stores the characters between the start marker '<' and the end marker '>'. 
When the end marker is encountered, the received string is saved into the receivedChars array and marked as new data (newData = true),
allowing the program to process this data afterward.


The `parseData()` function splits the input data, assuming it is sent in a string format with parts separated by commas. The extracted parts include:
- **G-code** (stored in `gCode`).
- **X, Y, Z coordinates** (stored in the variables `XCoordinate`, `YCoordinate`, `ZCoordinate`, corresponding to `R`, `S`, and `T`).
- **Offsets I and J** for calculating the center of the arc (stored in `cX` and `cY`).
*/

#ifndef _COMMUNICATIONS_H_
#define _COMMUNICATIONS_H_

#include <library.h>

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(gCode, strtokIndx); // copy it to gCode as string

  strtokIndx = strtok(NULL, ",");
  X_Coordinate = atof(strtokIndx); // my addition convert first part to an integer
  R = X_Coordinate;

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  Y_Coordinate = atof(strtokIndx);     // convert this part to an integer
  S = Y_Coordinate;

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  Z_Coordinate = atof(strtokIndx);     // convert this part to an integer
  T = Z_Coordinate;

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  I = atof(strtokIndx);     // convert this part to an integer
  cX = x1 + I; // centre radius is old X coordinate plus offset I

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  J = atof(strtokIndx);     // convert this part to an integer
  cY = y1 + J; // centre radius is old Y coordinate plus offset J
}

void showParsedData() {
  Serial.print("X = "); Serial.print (X_Coordinate);
  Serial.print("  Y = "); Serial.print (Y_Coordinate);
  Serial.print("  Z = "); Serial.print (Z_Coordinate);
  Serial.print("  G code Message "); Serial.println(gCode);
  Serial.print ("cX = "); Serial.println (cX);
  Serial.print ("cY = "); Serial.println (cY);
}


#endif