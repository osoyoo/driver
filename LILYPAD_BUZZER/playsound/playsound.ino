/******************************************************************************

LilyPad Buzzer Example

This example code shows how to hook up a LilyPad Buzzer to play a simple song 
using the tone() function and setting variables for each note.

Buzzer connections:
   * + pin to 9
   * - to -

******************************************************************************/
// Which pin the buzzer is attached to
int buzzerPin = 9;

// Delay in milliseconds
int delayTime = 500; 

// Notes and their frequencies
const int C = 1046;
const int D = 1175;
const int E = 1319;
const int F = 1397;
const int G = 1568;
const int A = 1760;
const int B = 1976;
const int C1 = 2093;
const int D1 = 2349;

void setup()
{
    // Set the buzzer pin as an OUTPUT
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  // Use the tone() function to play each note in a scale
  tone(buzzerPin, C);
  delay(delayTime);
  tone(buzzerPin, D);
  delay(delayTime);
  tone(buzzerPin, E);
  delay(delayTime);
  tone(buzzerPin, F);
  delay(delayTime);
  tone(buzzerPin, G);
  delay(delayTime);
  tone(buzzerPin, A);
  delay(delayTime);
  tone(buzzerPin, B);
  delay(delayTime);
  tone(buzzerPin, C1);
  delay(delayTime);
  // Use noTone() to shut off the buzzer and delay to create a 'rest'
  noTone(buzzerPin);
  delay(delayTime);
}

