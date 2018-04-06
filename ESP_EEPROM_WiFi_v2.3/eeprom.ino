void isiEEPROM1x()
{
  //Serial.println("Menulis EEPROM pertama kali");
  sprintf(data.SSID, "HME Lt.2"); // Memasukan tulisan "TES SSID" ke array SSID
  sprintf(data.SSIDpass, "");
  sprintf(data.AP, "Cek");
  sprintf(data.APpass, "ping");
  data.APch = 14;
  sprintf(data.host, "ub.ac.id");
  EEPROM.begin(128);
  EEPROM.put(6, data);
    EEPROM.end();
}

void bacaEEPROM()
{
  EEPROM.begin(128);
  //Serial.println("Membaca EEPROM");
  EEPROM.get(6, data);
  EEPROM.end();
}

void tulisEEPROM()
{
    EEPROM.begin(128);
  //Serial.println("tulis EEPROM");
  EEPROM.put(6, data);
    EEPROM.end();
}

