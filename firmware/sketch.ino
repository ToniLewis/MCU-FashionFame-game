const int TOP_BUTTON = 2;
const int BOTTOM_BUTTON = 3;
const int SHOES_BUTTON = 4;
const int ACCESSORY_BUTTON = 5;
const int CONFIRM_BUTTON = 6;

const int BUZZER = 8;
const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

const unsigned long DEBOUNCE_MS = 100;

// 0 = not selected, 1 = first choice, 2 = second choice
int topChoice = 0;
int bottomChoice = 0;
int shoesChoice = 0;
int accessoryChoice = 0;

// Game stats
int totalScore = 0;
int streak = 0;
int roundNumber = 0;

// Button debounce tracking
bool stableTop = HIGH;
bool stableBottom = HIGH;
bool stableShoes = HIGH;
bool stableAccessory = HIGH;
bool stableConfirm = HIGH;

bool lastTop = HIGH;
bool lastBottom = HIGH;
bool lastShoes = HIGH;
bool lastAccessory = HIGH;
bool lastConfirm = HIGH;

unsigned long changedTop = 0;
unsigned long changedBottom = 0;
unsigned long changedShoes = 0;
unsigned long changedAccessory = 0;
unsigned long changedConfirm = 0;

void setColor(bool red, bool green, bool blue) {
  digitalWrite(RED_LED, red ? HIGH : LOW);
  digitalWrite(GREEN_LED, green ? HIGH : LOW);
  digitalWrite(BLUE_LED, blue ? HIGH : LOW);
}

void beep(int frequency, int duration) {
  tone(BUZZER, frequency, duration);
}

void clearOutfit() {
  topChoice = 0;
  bottomChoice = 0;
  shoesChoice = 0;
  accessoryChoice = 0;
}

void showOutfit() {
  Serial.print("Outfit: Top=");
  Serial.print(topChoice);
  Serial.print(" | Bottom=");
  Serial.print(bottomChoice);
  Serial.print(" | Shoes=");
  Serial.print(shoesChoice);
  Serial.print(" | Accessory=");
  Serial.println(accessoryChoice);
}

bool buttonPressed(
  int pin,
  bool &stableState,
  bool &lastReading,
  unsigned long &lastChangeTime
) {
  bool reading = digitalRead(pin);

  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  bool newPress = false;

  if (millis() - lastChangeTime >= DEBOUNCE_MS) {
    if (reading != stableState) {
      stableState = reading;

      // INPUT_PULLUP means LOW = button pressed.
      if (stableState == LOW) {
        newPress = true;
      }
    }
  }

  lastReading = reading;
  return newPress;
}

void evaluateOutfit() {
  if (topChoice == 0 || bottomChoice == 0 ||
      shoesChoice == 0 || accessoryChoice == 0) {
    Serial.println("Choose all four outfit categories first!");
    setColor(false, false, true);
    beep(300, 250);
    delay(500);
    setColor(false, false, false);
    return;
  }

  roundNumber++;

  // Good rule 1: Red top + Black bottom + White shoes.
  // Good rule 2: Blue top + White bottom + Silver accessory.
  bool goodMatch =
    (topChoice == 1 && bottomChoice == 1 && shoesChoice == 1) ||
    (topChoice == 2 && bottomChoice == 2 && accessoryChoice == 2);

  Serial.println("----- RESULT -----");
  Serial.print("Round: ");
  Serial.println(roundNumber);
  showOutfit();

  if (goodMatch) {
    totalScore += 10;
    streak++;

    Serial.println("GOOD MATCH! +10 points");
    Serial.print("Total score: ");
    Serial.println(totalScore);
    Serial.print("Winning streak: ");
    Serial.println(streak);

    setColor(false, true, false);
    beep(1100, 250);
  } else {
    streak = 0;

    Serial.println("STYLE CLASH! Try another combination.");
    Serial.print("Total score: ");
    Serial.println(totalScore);
    Serial.println("Winning streak reset to 0.");

    setColor(true, false, false);
    beep(250, 350);
  }

  delay(900);
  setColor(false, false, false);
  clearOutfit();

  Serial.println("New round started.");
  Serial.println("-------------------");
}

void setup() {
  Serial.begin(9600);

  pinMode(TOP_BUTTON, INPUT_PULLUP);
  pinMode(BOTTOM_BUTTON, INPUT_PULLUP);
  pinMode(SHOES_BUTTON, INPUT_PULLUP);
  pinMode(ACCESSORY_BUTTON, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  setColor(false, false, false);

  Serial.println("=== Mix & Match Runway ===");
  Serial.println("Buttons cycle their category between Choice 1 and Choice 2.");
  Serial.println("Press Confirm to score your complete outfit.");
  Serial.println("-------------------");
}

void loop() {
  if (buttonPressed(TOP_BUTTON, stableTop, lastTop, changedTop)) {
    topChoice = (topChoice % 2) + 1;
    Serial.print("BTN:TOP -> Choice ");
    Serial.println(topChoice);
    beep(700, 80);
  }

  if (buttonPressed(BOTTOM_BUTTON, stableBottom, lastBottom, changedBottom)) {
    bottomChoice = (bottomChoice % 2) + 1;
    Serial.print("BTN:BOTTOM -> Choice ");
    Serial.println(bottomChoice);
    beep(750, 80);
  }

  if (buttonPressed(SHOES_BUTTON, stableShoes, lastShoes, changedShoes)) {
    shoesChoice = (shoesChoice % 2) + 1;
    Serial.print("BTN:SHOES -> Choice ");
    Serial.println(shoesChoice);
    beep(800, 80);
  }

  if (buttonPressed(ACCESSORY_BUTTON, stableAccessory, lastAccessory, changedAccessory)) {
    accessoryChoice = (accessoryChoice % 2) + 1;
    Serial.print("BTN:ACCESSORY -> Choice ");
    Serial.println(accessoryChoice);
    beep(850, 80);
  }

  if (buttonPressed(CONFIRM_BUTTON, stableConfirm, lastConfirm, changedConfirm)) {
    Serial.println("BTN:CONFIRM");
    evaluateOutfit();
  }
}