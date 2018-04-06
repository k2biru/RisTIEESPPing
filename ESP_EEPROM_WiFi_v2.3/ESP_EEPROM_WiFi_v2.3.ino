 // v2.2 penambahan fitur WiFi AP

#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP_EEPROM.h>
#include <stdio.h>

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*/ Alokasi EEPROM
  total 128

  ======
  00 Pertanda | 1 = EEPROM sudah diisi | 0= EEPROM kosong

  06 SSID ~
  20 SSID

  21 SSID pass~
  35 SSID pass

  36 APSSID ~
  50 APSSID

  51 APSSID pass ~
  65 APSSID pass

  66 AP CH

  67 Host~
  112 Host

*/
#define MAX_BUFFER 100


struct EEPROMStruct {
  char SSID[15], SSIDpass[15], AP[15], APpass[15], host[50];
  byte APch;
} data;
char str[2][16]; // untuk buffer LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);

ESP8266WebServer server(80);


void setup() {
  Wire.pins(0,2);
  Wire.begin(0,2);
  WiFi.mode(WIFI_AP_STA);

  Serial.begin(9600);
  //Serial.println(sizeof(EEPROMStruct));
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  EEPROM.begin(128);

  // Inisialisais LCD
  lcd.begin();
  lcd.backlight();


  // Bila EEPROM Belum disi maka diisi data default
  // Sementara belum di implementasikan
  Serial.println("Isi EEPROM ");
  Serial.print(EEPROM.percentUsed());
  Serial.println("%");
  bacaEEPROM();
  if (EEPROM.percentUsed() == 0)
  {
    isiEEPROM1x();
  }
  bacaEEPROM();
  // WiFi.softAP("PAPAS", "DD", 2);
  buatAPWifi();
  tampilLCD();
  delay(1000);
  sambungSSID();
  server.on ("/", handleHome);
  server.on ("/update", handleSentData);// bila berada di index server
  server.on ("/restart", handleRestart);
  server.onNotFound ( handleNotFound );
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  tampilLCD();
  if (cekSambunganSSID()) {
    cekPing();
  }
  //IPAddress myIP = WiFi.softAPIP();
  //Serial.println(myIP);
  server.handleClient();


}

void prosesLCD()
{

}

void tampilLCD()
{
  lcd.setCursor(0, 0);
  lcd.printstr(str[0]);
  lcd.setCursor(0, 1);
  lcd.printstr(str[1]);
  if (!cekSambunganSSID())
  {
    lcd.setCursor(15, 0);
    lcd.print("!");
  } else
  {
    lcd.setCursor(15, 0);
    lcd.print("  ");
  }
}




void cekPing()
{
  Serial.println("Cek Ping");
  digitalWrite(D9, HIGH);
  digitalWrite(D10, HIGH);
  delay(100);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  sprintf(str[0], "%s                ", data.host);
  if (Ping.ping(data.host)) {
    sprintf(str[1], "Ping : %d ms    ", Ping.averageTime());
  } else {
    sprintf(str[1], "Unreachable");
  }
  Serial.println(str[0]);
  Serial.println(str[1]);
}

void restartESP()
{
  lcd.setCursor(0, 0);
  lcd.printstr("::Restart::");
  lcd.setCursor(0, 1);
  lcd.printstr("+++");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.printstr("+++++");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.printstr("+++++++");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.printstr("++++++++++");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.printstr("+++++++++++++++#");
  delay(1000);
  ESP.restart();
}
