#include <WiFiManager.h>
#include <WebServer.h>

WiFiManager wm;
const char* ssid = "test";
const char* password = "cegenredemdp";
WebServer server(80);

void handleRoot()
{
    String page = "<!DOCTYPE html>";
    page += "<head>";
    page += "    <title>Serveur ESP32</title>";
    page += "    <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'/>";
    page += "</head>";

    page += "<body lang='fr'>";
    page += "    <h1>Serveur</h1>";
    page += "    <p>Ce serveur est hébergé sur un ESP32</p>";
    page += "    <b>Créé par Mathieu VIEL</b>";
    page += "</body>";

    page += "</html>";

    server.send(200, "text/html", page);
}
void handleNotFound()
{
    server.send(404, "text/plain", "404: Not found");
}

void setup()
{
    Serial.println("Erreur de connexion.");
  else
    Serial.println("Connexion etablie!");

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Serveur web actif!");
}

void loop()
    wm.resetSettings();
    ESP.restart();
  }
  server.handleClient();
}
