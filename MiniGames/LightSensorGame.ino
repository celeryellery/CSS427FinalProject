#define MAX_TONE 880 // Hz
#define MIN_TONE 220 // Hz
#define TONE_OFFSET 50 // tone must be at least 50 Hz greater than MIN_TONE and 50 Hz smaller than MAX_TONE
#define TONE_TOLERANCE 20 // a steady pitch within 20 Hz of the target value will win the game
#define LIGHT_SENSOR_RANGE 300 // sensor val
#define NUM_CALIBRATION_READINGS 10 // number of readings to calibrate sensor
#define DELAY_BETWEEN_CALIBRATION_READINGS 50 // ms
#define LIGHT_SENSOR_PIN 0 // A0
#define TONE_COUNT_TO_WIN 10; // number of consecutive correct tone readings to win

int correctToneCount = 0; // number of correct tone outputs in a row
int sensorMin = 0;
int sensorMax = 0;
int lightSensorVal = 0;
int output = 0;
int winningTone = 0; // tone that must be matched to win the game

// performs setup routine for the Light Sensor Game (calibration)
void setupLightSensorGame()
{
  resetLightSensorGame(); // incase of manual reset
  sensorMin = calibrateLightSensor();
  sensorMax = sensorMin + LIGHT_SENSOR_RANGE;
}

// main loop for the Light Sensor Game
void playLightSensorGame()
{
  setupLightSensorGame();
  Serial.println("\nLet's play the Light Sensor Game!");
  delay(1000);
  playNote();
  
  // loop until the player wins by holding the correct tone for the specified amount of readings
  do 
  {
    // map sensor input into Tone Hz output
    lightSensorVal = analogRead(LIGHT_SENSOR_PIN);
    output = map(lightSensorVal, sensorMin, sensorMax, MIN_TONE, MAX_TONE);
    output = constrain(output, MIN_TONE, MAX_TONE); // prevent tones outside this range
    
    tone(BEEP, output);
  } while (!checkForCorrectTone(output));
  // player wins
  Serial.println("You win the Light Sensor Game!");
  resetLightSensorGame();
  delay(2500);
  noTone(BEEP);
  delay(2500);
}

// plays the note that the player must replicate
void playNote()
{
  delay(1000);
  // play a random tone
  winningTone = random() % (MAX_TONE - MIN_TONE - TONE_OFFSET * 2) + MIN_TONE + TONE_OFFSET;
  tone(BEEP, winningTone, 1000);
  delay(2000);
}

// takes ambient light readings to set the minimum light value
int calibrateLightSensor()
{
  int sum = 0, count = 0;
  while (count < NUM_CALIBRATION_READINGS)
  {
    sum += analogRead(LIGHT_SENSOR_PIN);
    count++;
    delay(DELAY_BETWEEN_CALIBRATION_READINGS);
  }
  
  return sum / count; // return the average reading
}

// check if the player has held the correct tone for long enough to win
bool checkForCorrectTone(int playerTone)
{
  // if the player's tone is within a tolerable range of the winning tone
  if (playerTone > winningTone - TONE_TOLERANCE && playerTone < winningTone + TONE_TOLERANCE)
    correctToneCount++;    
  else
    correctToneCount = 0;
  
  return correctToneCount == TONE_COUNT_TO_WIN;
}

// resets the LightSensorGame
void resetLightSensorGame()
{
  correctToneCount = 0;
  sensorMin = 0;
  sensorMax = 0;
  lightSensorVal = 0;
  output = 0;
  winningTone = 0;
}
