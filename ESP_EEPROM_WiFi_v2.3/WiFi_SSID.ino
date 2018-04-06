void sambungSSID()
{
  //Serial.println("Sambung SSID");
  WiFi.begin(data.SSID, data.SSIDpass);
  sprintf(str[0], "Conn >> WiFi");
  sprintf(str[1], "%s",data.SSID);
  ////Serial.println("Connecting to WiFi");
}

boolean cekSambunganSSID()
{
  //Serial.println("Cek Sambungan");
  return (WiFi.status() == WL_CONNECTED) ? 1 : 0 ;
}

