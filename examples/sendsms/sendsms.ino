#include <ESP8266WiFi.h>
#include <SmsGlobal.h>

const char *ssid = "<wifi_ssid>";
const char *password = "<wifi_password>";

const char *sms_global_user = "<user>";
const char *sms_global_password = "<password>";

const char *sms_to = "<mobile_number>";

SmsGlobal smsGlobal(sms_global_user, sms_global_password);

void setup() {
  Serial.begin(115200);

  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  smsGlobal.send("ESP2866", sms_to, "Hello!");

  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(3e8); // 5 minutes
}

void loop() { }