// COD ESP8266 NODE MCU
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

//nume și parolă locală Wifi network
const char* ssid = "Home_2.4";
const char* password = "@H2311d!";

//datele de pe senzori primite de la placuta arduino
String data = " "; //intreaga informatie transmisa de placa Arduino catre modul
String t = " "; //temperatura
String h = " "; //umiditate aer
String hs = " "; //umiditate sol
char c;

//cream un server pe port-ul 80
AsyncWebServer server(80);

//codul paginii web
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
<style>
html {
font-family: Arial;
display: inline-block;
margin: 0px auto;
text-align: center;
}
h2 { font-size: 2.0rem; }
p { font-size: 2.0rem; }
.units { font-size: 1.2rem; }
.dht-labels{
font-size: 1.5rem;
vertical-align:middle;
padding-bottom: 15px;
}
</style>
</head>
<body>
<h2>Welcome to my GreenHouse App!</h2>

<p>
<i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
<span class="dht-labels"> Temperature </span>
<span id="temperature">%TEMPERATURE%</span>
<sup class="units">&degC</sup>
</p>

<p>
<i class="fas fa-tint" style="color:#00add6;"></i>
<span class="dht-labels">Humidity</span>
<span id="humidity">%HUMIDITY%</span>
<sup class="units">%</sup>
</p>

<p>
<i class="fas fa-seedling" style="color:#059e8a;"></i>
<span class="dht-labels">Soil moisture</span>
<span id="moisture">%MOISTURE%</span>
<sup class="units">%</sup>
</p>

</body>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
if(var == "TEMPERATURE"){
return String(t);
}
else if(var == "HUMIDITY"){
return String(h);
}
else if(var == "MOISTURE"){
return String(hs);
}
return String();
}


void setup(){

Serial.begin(115200);
// Connect to Wi-Fi
WiFi.enableInsecureWEP(true); 
WiFi.begin(ssid, password);
Serial.println("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println(".");
}

// Print ESP8266 Local IP Address
Serial.println(WiFi.localIP());

// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/html", index_html, processor);
});
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(t).c_str());
});
server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(h).c_str());
});
server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(hs).c_str());
});

// Start server
server.begin();
}

//cod program
void loop() {

  //avem cel putin un caracter in buffer-ul serial
  if(Serial.available()){
    //asteptam sa intre mai multe caractere in buffer  
    delay(50);
    //curatam ce s-a stocat la ultimul update in string-ul in care preluam informatia din buffer
    t = " ";
    h = " ";
    hs = " ";
    data = " ";
    //preluam datele pa care placa Arduino le transmite serial
    while(Serial.available()){
      c = Serial.read();
      data.concat(c);
      t = data.substring(1,6);
      h = data.substring(6,11);
      hs = data.substring(11,13);
    }
    Serial.println(t);
    Serial.println(h);
    Serial.println(hs);
  }
 
}
