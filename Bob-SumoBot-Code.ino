const int brightness = 27;
const int LED_PIN = 48;

const int WeaponInput = 17;
const int ServoPinR = 13;
const int ServoPinL = 12;
int WeaponVal = 0;

const int frequencyWeapons = 50;
const int resolutionWeapons = 14;
const int frequencyMotor = 1000;
const int resolutionMotor = 10;
const int RearMotorPinLF = 11;
const int FrontMotorPinLF = 9;
const int RearMotorPinLB = 10;
const int FrontMotorPinLB = 8;
const int ThrottleInput = 7;
int ThrottleVal = 0;

int getPWM(int pin)
{
  int highTime = pulseIn(pin, HIGH, 50000UL);  // 50 millisecond timeout
  int lowTime = pulseIn(pin, LOW, 50000UL);  // 50 millisecond timeout
  if((highTime == 0) || (lowTime == 0)){
    return 9;
  }else{
    // pulseIn() returns zero on timeout
    return (100 * highTime) / (highTime + lowTime);  // highTime as percentage of total cycle time
  }
}

void setup() 
{
  Serial.begin(115200);
  ledcAttach(RearMotorPinLF, frequencyMotor, resolutionMotor);
  ledcAttach(FrontMotorPinLF, frequencyMotor, resolutionMotor);
  ledcAttach(RearMotorPinLB, frequencyMotor, resolutionMotor);
  ledcAttach(FrontMotorPinLB, frequencyMotor, resolutionMotor);
  ledcAttach(ServoPinR, frequencyWeapons, resolutionWeapons);
  ledcAttach(ServoPinL, frequencyWeapons, resolutionWeapons);
  pinMode(ThrottleInput, INPUT);
  pinMode(WeaponInput, INPUT);
}

void loop() 
{
  ThrottleVal = getPWM(ThrottleInput);
  if(ThrottleVal > 9){
    rgbLedWrite(LED_PIN, 0, 255, 0); //forward is green
    Serial.println("forward");
    ledcWrite(RearMotorPinLF, 1000);
    ledcWrite(FrontMotorPinLF, 1000);
    ledcWrite(RearMotorPinLB, 0);
    ledcWrite(FrontMotorPinLB, 0);
  }else if(ThrottleVal < 9){
    rgbLedWrite(LED_PIN, 255, 0, 0); //backward is red
    Serial.println("backward");
    ledcWrite(RearMotorPinLF, 0);
    ledcWrite(FrontMotorPinLF, 0);
    ledcWrite(RearMotorPinLB, 1000);
    ledcWrite(FrontMotorPinLB, 1000);
  }else{
    rgbLedWrite(LED_PIN, 0, 0, 255); //neutral is blue
    ledcWrite(RearMotorPinLF, 0);
    ledcWrite(FrontMotorPinLF, 0);
    ledcWrite(RearMotorPinLB, 0);
    ledcWrite(FrontMotorPinLB, 0);
  }

  WeaponVal = getPWM(WeaponInput);
  Serial.println(WeaponVal);
  if(WeaponVal == 11){
    Serial.println("down");
    ledcWrite(ServoPinR, 500);
    ledcWrite(ServoPinL, 1000);
  }else if(WeaponVal == 8){
    Serial.println("up");
    ledcWrite(ServoPinR, 1000);
    ledcWrite(ServoPinL, 500);
  }else{
    Serial.println("neutral");
    ledcWrite(ServoPinR, 750);
    ledcWrite(ServoPinL, 750);
  }
  delay(10);
  
}