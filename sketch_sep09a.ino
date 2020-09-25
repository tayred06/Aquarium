const int led = 2;
unsigned int compteur = 0;

void setup(){
  Serial.begin(115200);
  Serial.println("TEST");

  pinMode(led, OUTPUT);
}

void loop(){
  Serial.println("Boucle" + String(compteur));
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  compteur++;
}
