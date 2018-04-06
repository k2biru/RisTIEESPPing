
/// HTTP 404
void handleNotFound() {
  server.send(404, "text/html", "<h1>Kosongan Satu porsi :: 404 :: </h1>");
}

/// HTTP / (home)
void handleHome()
{
  String text;
  byte i ;
  char temp[20];
  byte n = WiFi.scanNetworks();
  WiFi.hostname().toCharArray(temp, 20);
  text = "<html><head><title>Pengaturan ESP Ping"; text += temp;
  text += "</title><style>body{background-color:#cccccc;font-family:Arial,Helvetica,Sans-Serif;Color:#000088;}";
  text += "</style></head><body><h1>Pengaturan ESP Ping ["; text += temp; text += "]</h1>";
  text += "<p>Halaman  pengaturan"; text += temp;
  text += "</p><table><tr><th>=========</th><th>=========</th><th>=========</th></tr>";
  text += "<tr><th><a href='#'>[DEBUG]</a></th><th><a href='/restart'>[RESTART]</a></th><th><a href='#'>[CONFIG]</a></th></tr>";
  text += "<tr><th>=========</th><th>=========</th><th>=========</th></tr></table><br>";
  text += "<p>Setting Wifi</p><form method='POST' action='/update' target='_blak'>";
  text += "SSID:<input type='text' name='newSSID' value='"; text += data.SSID; text += "'><br>Pass:<input type='password' name='newPass' value='"; //text += pass;
  text += "'> [Opsional]<br>";
  text += "<input type='submit' value='Save'></form><br>";
 
  text += "<a href='/'>==|Refresh Jaringan [SSID]|==</a><br>";
  if (n == 0) text += " !! Tidak ada Jaringan Tersedia !! <br>";
  else {
    text += "====== Jaringan Tersedia ======<br><table><tr><th>SSID</th><th>RSSI</th><th>Encryption</th>";
    for (i= 0; i < n; i++)
    {
      text += "<tr><th>"; text += WiFi.SSID(i); text += "</th><th>"; text += WiFi.RSSI(i); text += "</th><th>"; text += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*" ;
      text += "</th></tr>";
      delay(10);
    }
    text += "</table><br>===============================<br>";

  }
  text += "<br><br><p>Pengaturan AP</p>[Acces Point]<br><form method='POST' action='/update' target='_blak'>";
  text += "AP SSID :<input type='text' name='newAPSSID' value='"; text += data.AP; text += "'><br>";
  text += "AP Pass :<input type='password' name='newAPPass' value='";// text+= APPass;
  text += "'> [Opsional] (kosong berarti tanpa password)<br>";
  text += "Channel:<select name='newAPCh'>";
  for (i = 1; i <= 14; i++)
  {
    text += "<option";
    text += " value='"; text += String(i); text += "'"; if (data.APch == i)text += " selected";
    text += ">Channel "; text += String(i);
    text += "</option>";
  }
  text += "</select>";
  text += "<input type='submit' value='Save'></form>";

  text += "<br> DEBUG ";
  text += "<br> host [host/ip]:"; text += data.host;
  text += " <br> last ping :";
  text += (int)Ping.averageTime();
  text += " ms<br>";
  
  text += "<br><br> [AP IP]        :";
  text += WiFi.softAPIP().toString();
  text += "<br> [Local IP]     :";
  text += WiFi.localIP().toString();
  text += "<br> [Station Name] :";
  text += WiFi.hostname();
  text += "<br><br>";

  text += "RisTIE Maret 2018 <a href='mailto:ristie@ub.ac.id'>RisTIE HME</a> v1.1 @512KB<br>(c) <a href='http://ristie.ub.ac.id'>RisTIE</a> HME-FT Universitas Brawijaya 2018<br>";
  text += "</body></html>";
  server.send ( 200, "text/html", text );
}

/// HTTP /update
void handleSentData() {
  String message = "SENT DATA<br><br>";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    //if (setting.debugUpdate)
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  server.send ( 200, "text/plain", message );         // mengirim data 200 (OK data diterima)ke pengirim
  if (server.arg("newAPSSID") != "")
  {
    server.arg("newAPSSID").toCharArray(data.AP, 15);
    if (server.arg("newAPSSID") != "") server.arg("newAPPass").toCharArray(data.APpass, 15);
    else sprintf(data.APpass, "");
    if (server.arg("newAPCh") != "") data.APch = server.arg("newAPCh").toInt();
    tulisEEPROM();
    restartESP();
  }
  if (server.arg("newSSID") != "")
  {
    server.arg("newSSID").toCharArray(data.SSID, 15);
    if (server.arg("newPass") != "")server.arg("newPass").toCharArray(data.SSIDpass, 15);
    else sprintf(data.SSIDpass, "");
    tulisEEPROM();
    restartESP();
  }
  if (server.arg("newHost") != "")
  {
    server.arg("newHost").toCharArray(data.host, 50);
    tulisEEPROM();
  }
}


/// HTTP /restart
void handleRestart()
{
  String message = " Restart the ESP in 5 Second<br><br>";
  server.send ( 200, "text/plain", message );
  restartESP();
}
