#include <WiFi.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define LIGHT 6  // Change to the light pin you are using.


/////////////////////////
/////////////////////////

int steps = 16;        //Set steps for 16-16-18.
int* stepptr = &steps; //pointer to reassign steps.
int count = 0;         //Set count at zero, should count forever.
int stepIndex = 0;  // Step position tracker


// Set HIGH/LOW based on the step sequence. This will vary based on your motor. 
// You can check your coils with either a multimeter or a piece of wire. Use continuity on multimeter or
// a piece of wire. Connect 2 motor pins with a single piece of wire. If they are part of the same coil, the motor
// should be more difficult to rotate by hand.

const int stepSequence[4][4] = {
  {HIGH, LOW, HIGH, LOW},  // Step 1
  {LOW, HIGH, HIGH, LOW},  // Step 2
  {LOW, HIGH, LOW, HIGH},  // Step 3
  {HIGH, LOW, LOW, HIGH}   // Step 4
};

// Wi-Fi credentials
// Wi-Fi credentials
const char* ssid     = "NETWORK";
const char* password = "PASSWORD";

// NTP server settings
const char* ntpServer = "time-e-g.nist.gov";
const long  gmtOffset = 0;      // GMT Offset (adjust for timezone)
const int   daylightOffset = 3600; // Daylight Savings Offset

WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, gmtOffset, daylightOffset);


void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  // Start with motor off
  disableMotor();
//////////////////////////wifi//////////////////////////////////////////////////
 Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Start NTP client
  timeClient.begin();

  // Wait for the time to sync
  Serial.print("Syncing time...");
  while (!timeClient.update()) {
    timeClient.forceUpdate();
    //Serial.print("."); // Show progress while updating time
  }
  Serial.println("Time synced!");

  // Get the Unix timestamp from NTP
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Current Unix Timestamp: ");
  Serial.println(epochTime);

  // Set the onboard RTC using the fetched Unix timestamp
  setTime(epochTime); // Set the onboard RTC to the Unix timestamp
  
  // Print the current time from RTC to verify
  Serial.print("RTC Time: ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" - Date: ");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.println(year());
/////////////////////////////////////////////////////////////////////////////////
}

void loop() {
  // Step the motor stepptr times smoothly.
  for (int i = 0; i < *stepptr; i++) {  //edited after
    stepMotor();
    delayMicroseconds(2000);  // Smooth movement with precise delay
  }

  // Turning off motor to prevent overheating. This dramatically reduced motor and motor controller temps.
  // They are now about room temperature.
  disableMotor();

  // This code makes up for uneven step numbers. For a true minute I need 16.666... steps.
  // This is not achievable with 200 steps per motor revolution (steps per rev may vary with motor type). 
  // So I make up for with 16-16-18.  
  //add 1 to count
  count++;

  int mod3 = count % 3;
  int mod9 = count % 9;

  if (mod9 == 0){ //probably not needed due to mod3 being below, but this code has near 100% accuracy, so I'm keeping it.
    *stepptr = 19;//if fast LOWER if slow RAISE. After video, it started running slow, raised to 19 rather than 18.
  }
  if (mod3 == 0){ //Every third step adds 2 steps to make up for 0.666... steps needed.
    *stepptr = 18;
  }
  else{
    *stepptr = 16;
  }
  ///////////////////////////////wifibelow////////////////////////////////////////////////////////
  timeClient.update();
  int currentHour = hour();
  int currentMinute = minute();
  int currentSecond = second();
  int currentDay = day();
  int currentMonth = month();
  int currentYear = year();

// converts utc to cst, unneeded
  // int currentHourCST = (currentHour - 6) % 24;  // Adjust for CST (UTC-6)
  // if (currentHourCST < 0) currentHourCST += 24;    // Handle negative wraparound

  /////////////////////////////////wifiabove/////////////////////////////////////////////////////////////
  if (currentHour >= 0 && currentHour < 13) {
    digitalWrite(LIGHT, HIGH); // Turn light ON between 8 PM - 7 AM CST
} else{
    digitalWrite(LIGHT, LOW);
}
  Serial.print("RTC Time: ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" - Date: ");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print("/");
  Serial.println(year());
// Wait 59.875 seconds. Not 60 seconds because motor takes approximately 0.125 seconds to move (steps).
  delay(59600);
}

void stepMotor() {

  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);

  // Move to the next step
  stepIndex = (stepIndex + 1) % 4;
}

// Function to disable motor and prevent overheating
// Turning off motor to prevent overheating. This dramatically reduced motor and motor controller temps.
// They are now about room temperature.
void disableMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
