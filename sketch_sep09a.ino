#include <WiFiManager.h>
WiFiManager wm;
const char* ssid = "test";
const char* password = "cegenredemdp";

void setup()
{
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");

  if(!wm.autoConnect(ssid, password))
    Serial.println("Erreur de connexion.");
  else
    Serial.println("Connexion etablie!");
}

void loop()
{
  //Dans cet exemple j'utilise la broche tactile D4 pour faire un reset des paramètres de connexion.
  if(touchRead(T0) < 50)
  {
    Serial.println("Suppression des reglages et redemarrage...");
    wm.resetSettings();
    ESP.restart();
  }
}
