#include <Arduino.h>
#include <SmsGlobal.h>
#include <WiFiClientSecure.h>

SmsGlobal::SmsGlobal(String user, String password) {
  _user = user;
  _password = password;
}

bool SmsGlobal::send(String from, String to, String text) {
  char *fingerprint = "6E 0A 2A CD 42 A5 8E A6 23 9B 63 D8 88 8B DF C5 2E D6 6F A7";
  String host = "api.smsglobal.com";
  int httpsPort = 443;

  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return false;
  }

  String url = "/http-api.php?action=sendsms"
               "&user=" + _user +
               "&password=" + _password +
               "&from=" + urlEncode(from) +
               "&to=" + urlEncode(to) +
               "&text=" + urlEncode(text);

  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url +
               " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String line = client.readStringUntil('\n');
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");

  if (line.startsWith("{\"state\":\"success\"")) {
    return true;
  } else {
    return false;
  }
}

// https://github.com/zenmanenergy/ESP8266-Arduino-Examples/blob/master/helloWorld_urlencoded/urlencode.ino
String SmsGlobal::urlEncode(String value)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < value.length(); i++){
      c=value.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}