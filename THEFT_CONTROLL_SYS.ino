#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// ================= LCD =================
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// ================= WiFi =================
SoftwareSerial wifi_serial(2, 3);

// ================= Motor Driver =================
#define ENA 4      // PWM
#define IN1 5      // Direction fixed

// ================= Other Pins =================
#define BUZZER 6
#define TILT_SENSOR 7>

String inputString = "";
boolean stringComplete = false;

const String validCard = "4D008BDED5CD";
boolean accessGranted = false;

// ================= WIFI OK CHECK =================
void okcheck() {
  while (true) {
    if (wifi_serial.available() > 0) {
      if (wifi_serial.read() == 'K') {
        return;
      }
    }
  }
}

// ================= SEND COMMAND =================
void sendcommand(String cmd) {
  wifi_serial.println(cmd);
  okcheck();
  delay(500);
}

// ================= TELNET SEND =================
void send_telnet(String message) {

  wifi_serial.print("AT+CIPSEND=0,");
  wifi_serial.println(message.length() + 2);
  delay(1000);

  wifi_serial.println(message);
  wifi_serial.print("\r\n");
  delay(2000);
}

// ================= WIFI INIT =================
void wifi_init() {

  sendcommand("AT");
  sendcommand("ATE0");
  sendcommand("AT+CWMODE=2");
  sendcommand("AT+CIPMUX=1");
  sendcommand("AT+CIPSERVER=1,23");

  lcd.clear();
  lcd.print("Waiting Telnet");

  // Wait for CONNECT message
  while (true) {
    if (wifi_serial.available()) {
      char c = wifi_serial.read();
      if (c == 'C') {   // CONNECT detected
        break;
      }
    }
  }

  lcd.clear();
  lcd.print("Telnet Connected");
  delay(2000);
  lcd.clear();
  lcd.print("Waiting Unlock");
}

// ================= MOTOR CONTROL =================
void motorStartSlow() {

  digitalWrite(IN1, HIGH);

  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(ENA, speed);
    delay(80);
  }
}

void motorStopSlow() {

  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(ENA, speed);
    delay(80);
  }

  analogWrite(ENA, 0);
}

// ================= SETUP =================
void setup() {

  Serial.begin(9600);
  wifi_serial.begin(115200);   // KEEP 115200 (your ESP default)

  lcd.begin(16, 2);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TILT_SENSOR, INPUT);

  lcd.print("IOT THEFT CTRL");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  wifi_init();
}

// ================= LOOP =================
void loop() {

  serialEvent();

  if (stringComplete) {

    lcd.clear();

    if (inputString == validCard) {

      accessGranted = true;

      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Vehicle Start");

      send_telnet("Authorized Access - Vehicle Starting");

      motorStartSlow();

      lcd.clear();
      lcd.print("System Running");

    } else {

      accessGranted = false;

      lcd.print("Invalid Card");
      lcd.setCursor(0, 1);
      lcd.print("Access Denied");

      digitalWrite(BUZZER, HIGH);
      send_telnet("Unauthorized Access Attempt!");
      delay(2000);
      digitalWrite(BUZZER, LOW);

      lcd.clear();
      lcd.print("Waiting Unlock");
    }

    inputString = "";
    stringComplete = false;
  }

  // ===== Accident Detection =====
  if (accessGranted == true) {

    if (digitalRead(TILT_SENSOR) == HIGH) {

      lcd.clear();
      lcd.print("Accident Detect");
      lcd.setCursor(0, 1);
      lcd.print("Vehicle Stop");

      send_telnet("ALERT! Accident Detected!");

      motorStopSlow();

      digitalWrite(BUZZER, HIGH);
      delay(3000);
      digitalWrite(BUZZER, LOW);

      lcd.clear();
      lcd.print("System Stopped");

      accessGranted = false;
      delay(2000);

      lcd.clear();
      lcd.print("Waiting Unlock");
    }
  }
}

// ================= RFID SERIAL =================
void serialEvent() {

  while (Serial.available()) {

    char inChar = Serial.read();

    if (inChar == '\n' || inChar == '\r')
      continue;

    if (isHexadecimalDigit(inChar)) {
      inputString += inChar;
    }

    if (inputString.length() >= 12) {
      inputString = inputString.substring(0, 12);
      stringComplete = true;
      break;
    }
  }
}