#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String temp = "25";
String heurePompe = "60";

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);

  display.display();
  delay(2000);


  testdrawchar(temp, heurePompe);

  Serial.println(F("Fin du setup"));

}

void loop() {
}

void testdrawchar(String temp, String heurePompe) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(1, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write("Adresse ip :\r\n 192.168.0.4 \r\n");
  display.write("Temperature :\r\n 25" + temp + " \r\n");
  display.write("Prochaine activation de la pompe :\r\n " + heurePompe + " minustes \r\n");

  display.display();
  delay(2000);
}
