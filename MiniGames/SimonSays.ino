// length of correct sequence to win
#define POINTS_TO_WIN 10

// pause before showing next sequence in ms
#define DELAY_BETWEEN_SEQUENCES 1000

int correctSequence[POINTS_TO_WIN] = { }; // the correct sequence that must be followed
int correctSequenceLength = 0;            // length of the current correct sequence that the player must follow
int playerSequenceLength = 0;             // length of the sequence player is currently inputting
bool isGameOverSimonSays = false;                        // condition if game is over

// sets up the pins necessary to play SimonSays
void setupSimonSays()
{
  resetSimonSays(); // incase of manual reset
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(3, OUTPUT); 
}

// plays a game of Simon Says
void playSimonSays()
{
  setupSimonSays();
  Serial.println("\nLet's play Simon Says!");
  delay(1000);
  while (!isGameOverSimonSays)
    playSimonSaysRound();
}

// plays a round of Simon Says
void playSimonSaysRound()
{
  correctSequence[correctSequenceLength++] = (random() % 4 + YELLOW); // yellow, blue, green, or red
  showSequence();
  playersTurn();
  delay(DELAY_BETWEEN_SEQUENCES);  
}

// shows the current correct sequence to the player before the player attempts to recreate it
void showSequence()
{
  for (int i = 0; i < correctSequenceLength; i++)
  {
     flashLED(correctSequence[i]);
  }
}

int getPlayerInput()
{
  // wait until the player makes a choice
  while (true)
  {
    if (digitalRead(REDSW) == 1)
    {
       flashLED(RED);
       return RED;
    }
    else if (digitalRead(GREENSW) == 1)
    {
       flashLED(GREEN);
       return GREEN;
    }
    else if (digitalRead(BLUESW) == 1)
    {
       flashLED(BLUE);
       return BLUE;
    }
    else if (digitalRead(YELLOWSW) == 1)
    {
       flashLED(YELLOW);
       return YELLOW;
    }
  }
}

bool processPlayerInput(int choice, int playerSequence[])
{
  playerSequence[playerSequenceLength++] = choice;
  return (playerSequence[playerSequenceLength - 1] == correctSequence[playerSequenceLength - 1]);  
}

void playersTurn()
{
  // reset player input
  int playerSequence[POINTS_TO_WIN] = { };
  playerSequenceLength = 0;

  // go until the player correctly matches the sequence or enters an incorrect choice
  while (playerSequenceLength < correctSequenceLength)
  { 
    int choice = getPlayerInput();                   // wait for the player to respond
    if (!processPlayerInput(choice, playerSequence)) // determine if the correct choice was made
    {
      gameOverSimonSays();                                    // end the game if the player chooses incorrectly
      break;
    }
  }
  if (playerSequenceLength == POINTS_TO_WIN)
    playerWin();
}

void gameOverSimonSays()
{
   for (int i = 0; i < 10; i++)
   {
     digitalWrite(RED, HIGH);
     delay(100);
     digitalWrite(RED, LOW);
     digitalWrite(GREEN, HIGH);
     delay(100);
     digitalWrite(GREEN, LOW);
     digitalWrite(BLUE, HIGH);
     delay(100);
     digitalWrite(BLUE, LOW);
     digitalWrite(YELLOW, HIGH);
     delay(100);
     digitalWrite(YELLOW, LOW);
   }
   resetSimonSays();
   isGameOverSimonSays = true;
}

void playerWin()
{
  Serial.println("You win Simon Says!");
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite(YELLOW, HIGH);
    delay(200);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(YELLOW, LOW);
    delay(200);
  }
  resetSimonSays();
  isGameOverSimonSays = true;
}

void resetSimonSays()
{
  isGameOverSimonSays = false;
   for (int i = 0; i < POINTS_TO_WIN; i++)
   {
      correctSequence[i] = 0;
      correctSequenceLength = 0;
      playerSequenceLength = 0;
   } 
}
