void setup() {
  // serial setup
  Serial.begin(9600);
}

struct userTimes {
  unsigned life;
  unsigned notify;
};

struct userTimes userInput(unsigned lifespan, unsigned notify_time) {
  userTimes UserTimes;
  // Make sure that notify time is less than lifespan
  if (notify_time >= lifespan) {
    Serial.println("Invalid notification time. Must be less than lifespan time.\n");
    return UserTimes;
  }
  
  // Convert lifespan and notify_time to seconds
  UserTimes.life = lifespan * 86400;
  UserTimes.notify = UserTimes.life - (notify_time * 86400);

  return UserTimes;
}

char timeCheck(unsigned t, unsigned checkTime) {
  // 86400 seconds in a day
  if (t >= checkTime) {
    return '1';
  }
  return '0';
}

void loop() {  
  // User Input Values
  userTimes UserTimes = userInput(14, 3);

  // Pin Mapping
  int analogPin = A0;
  int dailyLED = 11;
  int notifyLED = 10;
 
  unsigned daily = 0; // daily time elapsed in seconds

  while (1) {

    unsigned total = millis() / 1000;

    
    // char dailyAlert = timeCheck(86400 + daily, total);
    char dailyAlert = timeCheck(total, 5 + daily);
    if (dailyAlert == '1') {
      // turn on LED
      pinMode(dailyLED, OUTPUT);
      digitalWrite(dailyLED, HIGH);
    }
    // if Contact lense case is opened
    unsigned openCase = analogRead(analogPin);
    // Serial.print("analog read is: ");
    // Serial.println(test);
    if (openCase >= 10) {
      if (dailyAlert == '1') {
        digitalWrite(dailyLED, LOW);
      }
      daily = millis() / 1000;
      Serial.print("Daily is: ");
      Serial.println(daily);
    }
    
    // char replaceAlert = timeCheck(total, UserTimes.notify);
    char replaceAlert = timeCheck(total, 15);
    if (replaceAlert == '1' and total < 18) {
      // blink LED
      pinMode(notifyLED, OUTPUT);
      for (int i = 0; i < 4; i++) {
        delay(500);
        digitalWrite(notifyLED, HIGH);
        delay(500);
        digitalWrite(notifyLED, LOW);
      }
    }
  
    // char finalAlert = timeCheck(total, UserTimes.life);
    char finalAlert = timeCheck(total, 20);
    if (finalAlert == '1' and total < 25) {
      // turn on LED
      pinMode(notifyLED, OUTPUT);
      digitalWrite(notifyLED, HIGH);
      delay(3000);
      digitalWrite(notifyLED, LOW);
    }
    
    Serial.println(total);

  }
}
