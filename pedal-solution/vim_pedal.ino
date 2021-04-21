#include <Keyboard.h>

/**
 * STATUS list
 * 0: Normal status, waiting for press
 * 1/2: Insert/View mode, waiting for release Button I/V
 */
unsigned short STATUS_INSERT = 0;
// Removing joggle for pushing button

const int INSERT_MODE_BUTTON = 3; // Pin of I Mode
const int VIEW_MODE_BUTTON = 4;   // Pin of I Mode

void setup()
{
  // Set pull up (INPUT) mode for D2 and D3
  pinMode(INSERT_MODE_BUTTON, INPUT_PULLUP);
  pinMode(VIEW_MODE_BUTTON, INPUT_PULLUP);
  Keyboard.begin();
}

// Press single key
void pressSingleKey(char key, unsigned int delayMs)
{
  Keyboard.press(key);
  delay(delayMs);
  Keyboard.release(key);
}

// Press single key
void pressSingleKey(char key)
{
  pressSingleKey(key, 100);
}

const unsigned int JOGGLE_REMOVING = 20; //ms
/**
 * Check pin (button) status without joggling
 */
bool checkButtonStatus(int pin, bool expectedStatus)
{
  if (digitalRead(pin) == expectedStatus)
  {
    delay(JOGGLE_REMOVING);
    if (digitalRead(pin) == expectedStatus)
    {
      return true;
    }
  }
  return false;
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (STATUS_INSERT == 0)
  {
    if (checkButtonStatus(INSERT_MODE_BUTTON, LOW))
    {
      STATUS_INSERT = 1;
      pressSingleKey('I');
    }
    else if (checkButtonStatus(VIEW_MODE_BUTTON, LOW))
    {
      STATUS_INSERT = 2;
      pressSingleKey('V');
    }
  }
  else if (STATUS_INSERT == 1)
  {
    if (checkButtonStatus(INSERT_MODE_BUTTON, HIGH))
    {
      pressSingleKey(KEY_ESC);
      STATUS_INSERT = 0;
    }
  }
  else if (STATUS_INSERT == 2)
  {
    if (checkButtonStatus(VIEW_MODE_BUTTON, HIGH))
    {
      pressSingleKey(KEY_ESC);
      STATUS_INSERT = 0;
    }
  }
  else
  {
    // Should not be here.
    STATUS_INSERT = 0;
    setup();
  }
}