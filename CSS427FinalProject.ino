
#define LED 1
#define MELODIES 2

int gameMode = 0;
void setup() 
{
  // Initialize hardware setup
  initCapacitiveSensor();
  initMelodies();
 Serial.println("Game starts!!");
 
  Serial.begin(9600);
}

void loop() 
{
  // Display menu

  // Pick a game mode
  gameMode = 2;
  
  // Run selected game mode
  switch (gameMode)
  {
    case LED:
      
      break;
    case MELODIES:
      melodies();
      break;
  }
  
   delay(100);
}

