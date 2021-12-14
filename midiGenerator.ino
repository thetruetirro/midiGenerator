unsigned long lastStepTime = 0;
int stepLength = 500;
int currentNote = 0;
int currentRoot = 60;
unsigned long lastStepTimeRoot = 0;
int stepLengthRoot = 10000;
int majorScale[8] = {0, 2, 4, 5, 7, 9, 11, 12};
bool buttonState = LOW;
bool lastButtonState = LOW;
bool buttonOn = LOW;
int buttonPin = 32;
int lastNote = 0;
int lastRoot = 0;
int noteLight = 10;
int onOffLight = 12;
int stepMax = 0;
int thisIsTheChangeIAmMakingToMyCodeRightNow = 100;


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(noteLight, OUTPUT);
  pinMode(onOffLight, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  checkButtonOnOff();
  if (buttonOn == HIGH) {
    stepMax = map(analogRead(A14), 0, 1028, 100, 5000);
    analogWrite(onOffLight, 200);
    whatRoot();
    playRandomNote();
  } else {
    for (int i = 0; i < 127; i++) {
      usbMIDI.sendNoteOff(i, 100, 1);
    }
    analogWrite(onOffLight, 0);
    delay(5);
  }
}

void playRandomNote() {
  currentNote = random(0, 7);
  if (millis() > lastStepTime + stepLength) {
    lastStepTime = millis();
    usbMIDI.sendNoteOn(currentRoot + majorScale[currentNote], 100, 1);
    analogWrite(noteLight, 200);
    delay(500);
    usbMIDI.sendNoteOff(currentRoot + majorScale[currentNote], 100, 1);
    analogWrite(noteLight, 0);
    stepLength = random(100, stepMax);
  }
}


void whatRoot() {
  if (millis() > lastStepTimeRoot + stepLengthRoot) {
    lastStepTimeRoot = millis();
    lastRoot = currentRoot;
    currentRoot = random(53, 72);
  }
}

void checkButtonOnOff() {
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == LOW and buttonState == HIGH) {
    buttonOn = !buttonOn;
    delay(5);
  } else if (lastButtonState == HIGH and buttonState == LOW) {
    delay(5);
  }
}
