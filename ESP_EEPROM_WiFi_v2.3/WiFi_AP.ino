void buatAPWifi()
{
  //Serial.println("Memulai AP");
  WiFi.hostname(data.AP);
  WiFi.softAP(data.AP, data.APpass, data.APch);
  IPAddress myIP = WiFi.softAPIP();
  //Serial.println(myIP);
  sprintf(str[0], "AP %s", data.AP);
  sprintf(str[1], "%s",data.APpass);
}

