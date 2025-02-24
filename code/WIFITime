#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>  // Include TimeLib for setting the RTC

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
  Serial.begin(115200);
  Serial.println("Starting up...");

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Start NTP client
  timeClient.begin();

  // Wait for the time to sync
  Serial.print("Syncing time...");
  while (!timeClient.update()) {
    timeClient.forceUpdate();
    Serial.print("."); // Show progress while updating time
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
}

void loop() {
  // Nothing to do in loop
}
