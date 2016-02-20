#define TEMP_SENSOR_PIN 1 // A1
#define LED1 4 // D4
#define LED2 3 // D3
#define LED3 2 // D2
#define NUM_TEMP_LEDS 3 // number of LEDS used for the temperature sensor game
#define TEMP_RAISE_TO_WIN 6 // raise temp val to ambient temp + this to win
#define TEMP_COUNT_TO_WIN 10 // number of consecutive temp readings above winningTemp to win

int ambientTemp = 0;
int winningTemp = 0;
int playerTemp = 0;
int correctTempCount = 0;
int startTime = 0;

// calibrate the temperature sensor by taking multiple readings to determine the ambient temperature
int calibrateTempSensorGame()
{
  int sum = 0, count = 0;
  while (count < NUM_CALIBRATION_READINGS)
  {
    sum += analogRead(TEMP_SENSOR_PIN);
    count++;
    delay(DELAY_BETWEEN_CALIBRATION_READINGS);
  }
  
  return sum / count; // return the average reading 
}

// perform the necessary setup before playing the Temperature Sensor Game
void setupTempSensorGame()
{
  resetTempSensorGame(); // incase of manual reset
  ambientTemp = calibrateTempSensorGame();
  winningTemp = ambientTemp + TEMP_RAISE_TO_WIN;
  startTime = millis();
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

// the main game logic loop of the Temperature Sensor Game
void playTempSensorGame()
{
  setupTempSensorGame();
  Serial.println("\nLet's play the Temp Sensor Game!");
  
  // loop until the target temperature is held for a period of time
  do
  {
    playerTemp = analogRead(TEMP_SENSOR_PIN); // read the sensor
    // light the LEDs to represent the current temperature
    lightTempLEDs();
  } while (!checkForCorrectTemp(playerTemp));
  
  // the player wins when the target temperature is held for a time
  tempSensorGameWin();
}

// check to see if the current sensor reading has been 
// equal to or greater than the target value for long enough
bool checkForCorrectTemp(int temp)
{
  if (playerTemp >= winningTemp)
    correctTempCount++;
  else
    correctTempCount = 0;
  return correctTempCount == TEMP_COUNT_TO_WIN; 
}

// control the lighting of the LEDs based on temperature readings
void lightTempLEDs()
{
   if (playerTemp >= ambientTemp + TEMP_RAISE_TO_WIN / NUM_TEMP_LEDS)
     digitalWrite(LED1, HIGH);
   else
     digitalWrite(LED1, LOW);
   if (playerTemp >= ambientTemp + TEMP_RAISE_TO_WIN / NUM_TEMP_LEDS * 2)
     digitalWrite(LED2, HIGH);
   else
     digitalWrite(LED2, LOW);
   if (playerTemp >= ambientTemp + TEMP_RAISE_TO_WIN)
     digitalWrite(LED3, HIGH);
   else
     digitalWrite(LED3, LOW);   
}

// handles the event that the player wins the Temperature Sensor Game
void tempSensorGameWin()
{
  Serial.print("You win the Temp Sensor Game! Your time was: "); 
  Serial.print((float)(millis() - startTime) / 1000);
  Serial.println(" second(s)");
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(200);
  }
  delay(2000);
  resetTempSensorGame();
}

// resets all of the variables related to the Temperature Sensor Game
void resetTempSensorGame()
{
  ambientTemp = 0;
  winningTemp = 0;
  playerTemp = 0;
  correctTempCount = 0;
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}
