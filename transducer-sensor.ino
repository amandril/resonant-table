int inputPin1 = A0;
int inputPin2 = A1;
int inputPin3 = A2;
int inputPin4 = A3;
// 1 (δ, Δ) Mathematics variation of a variable or function.
float deltaA = 0;
float deltaB = 0;
float deltaC = 0;
float deltaD = 0;

float oldVal1 = 0;
float oldVal2 = 0;
float oldVal3 = 0;
float oldVal4 = 0;

boolean play = false;
boolean prevPlay = false;

void setup() {
  analogReadResolution(12);
  Serial.begin(115200);
}

float calDelta(float d, float i, float o, float factor) {
  float v = (d*factor + abs(i-o))/(factor+1);
//  o = i;
  return v;
}

void loop() {
  // put your main code here, to run repeatedly:
  float inputVal1 = analogRead(inputPin1);
  float inputVal2 = analogRead(inputPin2);
  float inputVal3 = analogRead(inputPin3);
  float inputVal4 = analogRead(inputPin4);
  //  val = (inputVal + val) / 2; // Smoothing function

  float smoothing = 8;
  float threshold = 15;

  deltaA = calDelta(deltaA, inputVal1, oldVal1, smoothing);
  deltaB = calDelta(deltaB, inputVal2, oldVal2, smoothing);
  deltaC = calDelta(deltaC, inputVal3, oldVal3, smoothing);
  deltaD = calDelta(deltaD, inputVal4, oldVal4, smoothing);

  float delta = (deltaA + deltaB + deltaC +deltaD)/4;

  Serial.print(delta);
  Serial.print(" ");
  Serial.print(threshold);
  Serial.print(" ");
  Serial.print(deltaA);
  Serial.print(" ");
  Serial.print(deltaB);
  Serial.print(" ");
  Serial.print(deltaC);
  Serial.print(" ");
  Serial.print(deltaD);
  Serial.println();
  if (delta >= threshold) {
    play = true;
//    tone(A1, (deltaA*(deltaA/10))/10, 10);
//    tone(A4, 5+floor((delta/1.5)), 10);
    tone(A4, 5+floor((delta*10)), 10);
  } else {
    play = false;
//    noTone(A1);
  }

//  if (!prevPlay && play) {
//    tone(A1, (deltaA*(deltaA/10))/10, 10);
//  }

  if (prevPlay && !play) {
    noTone(A4);
  }
  
  delay(10);
  oldVal1 = inputVal1;
  oldVal2 = inputVal2;
  oldVal3 = inputVal3;
  oldVal4 = inputVal4;
  prevPlay = play;
}
