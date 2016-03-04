// define pins for the switches (used in Simon Says and the Main Menu)
#define REDSW    5
#define GREENSW  6
#define BLUESW   7
#define YELLOWSW   22

// time that each LED spends on and off when flashing
#define DELAY_BETWEEN_LEDS 500

// pin for sound
#define BEEP 5 // D5

// analog input pin for seeding random() with noise
#define RANDOM_SEED_PIN 5 // A5

void setup() 
{
  Serial.begin(9600); // baud
  randomSeed(analogRead(RANDOM_SEED_PIN));     // seed the random function with noise on analog input pin 5
  setupSimonSays();
  setupLightSensorGame();
  setupTempSensorGame();
}

void loop() 
{
  //playDDR();
  //playTempSensorGame();
  //playLightSensorGame();
  //playSimonSays();
  mainMenu();
}

// allow the player a choice of which game to play
int mainMenu()
{
  // show the player the available games to choose from
  displayGames();
  
  // let the player select which game to play
  int playerChoice = selectGame();
  switch(playerChoice)
  {
     case REDSW:
       playSimonSays();
     break;
     
     case GREENSW:
       playLightSensorGame();
     break;
     
     case BLUESW:
       playDDR();
     break;
     
     default: 
       playSimonSays();
     break;
  }
}

void displayGames()
{
  Serial.println("\nPlease choose a game to play."); 
  Serial.print("Simon Says (red)"); Serial.print("\tLight Sensor Game (green)"); Serial.println("\tTemp Sensor Game (blue)");
}

// the player selects which game to play with one of the push buttons
int selectGame()
{
  int playerChoice = 0;
  while (playerChoice == 0)
  {
     playerChoice = digitalRead(REDSW);
     if (playerChoice != 0)
     {
       playerChoice = REDSW; 
       break;
     }
     playerChoice = digitalRead(GREENSW);
     if (playerChoice != 0)
     {
       playerChoice = GREENSW; 
       break;
     }
     playerChoice = digitalRead(BLUESW);
     if (playerChoice != 0)
     {
       playerChoice = BLUESW; 
       break;
     }
     playerChoice = digitalRead(YELLOWSW);
     if (playerChoice != 0)
     {
       playerChoice = YELLOWSW; 
       break;
     }
  }
  return playerChoice;  
}

void flashLED(int LED)
{
  tone(BEEP, LED * 20, 500);
  digitalWrite(LED, HIGH);
  delay(DELAY_BETWEEN_LEDS);
  digitalWrite(LED, LOW);
  delay(DELAY_BETWEEN_LEDS);
}

