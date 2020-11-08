#include <WiFiManager.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

WiFiManager wm;
const char* ssid = "test";
const char* password = "cegenredemdp";
AsyncWebServer server(80);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String temp = "20";
String heurePompe = "60";

const char* PARAM_INPUT_1 = "temp";
const char* PARAM_INPUT_2 = "heure";

const char index_html[] PROGMEM = R"rawliteral(
<html lang='fr'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>Aquarium Connecté</title>
    <link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>
    <style>
        #corp {
            padding-left: 20%;
            padding-right: 20%;
        }
        h1 {
            text-align: center;
        }
        select {
            width: 50px!important;
        }
    </style>
</head>
<body>
    <div class='w3-card w3-blue w3-padding-small w3-jumbo w3-center'>
        <h1>AQUARIUM CONNECTE</h1>
    </div>
    <br>
    <div id='corp'>
        <form action='/get'>
            <p>Température: + temp +</p>
            <p>Changer la température : <input type='number' name='temp' id='temp' style='width:75px;'></p>
            <br>
            <p>Etat de la pompe: </p>
            <p>Activer la pompe (15 minutes) tout les 
                <select class='w3-select' name='heure' id='heure'>
                    <option value='10'>10</option>
                    <option value='20'>20</option>
                    <option value='30'>30</option>
                    <option value='40'>40</option>
                    <option value='50'>50</option>
                    <option value='60'>60</option>
                    <option value='70'>70</option>
                    <option value='80'>80</option>
                    <option value='90'>90</option>
                </select>
             minutes</p>
             <button class='w3-btn w3-blue w3-block'>Appliquer</button>
        </form>
        
    </div>
</body>
</html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void testdrawchar(String temp, String heurePompe) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(1, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write("Adresse ip :\r\n 192.168.0.4 \r\n");
  display.write("Temperature :\r\n deg \r\n");
  display.write("Prochaine activation de la pompe :\r\n \r\n");
  

  display.display();
  delay(2000);
}

void setup()
{
  WiFi.mode(WIFI_STA);

  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  // Clear the buffer
  display.clearDisplay();
  display.display();
  testdrawchar(temp, heurePompe);


  if(!wm.autoConnect(ssid, password))
    Serial.println("Erreur de connexion.");
  else
    Serial.println("Connexion etablie!");

  server.begin();

  Serial.println("Serveur web actif!");
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
    });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      temp = request->getParam(PARAM_INPUT_1)->value();

      heurePompe = request->getParam(PARAM_INPUT_2)->value();
  });
}

void loop(){
  //Dans cet exemple j'utilise la broche tactile D4 pour faire un reset des paramètres de connexion.
  if(touchRead(T0) < 50)
  {
    Serial.println("Suppression des reglages et redemarrage...");
    wm.resetSettings();
    ESP.restart();
  }

}
