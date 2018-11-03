#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

// Reles Pins
const int RELE_0 = 2;
const int RELE_1 = 3;

// Messages
const String RELE_RECEIVE = "Message received";

//Ethernet configuration
byte mac[] = { 0x90, 0xA1, 0xDA, 0x0E, 0xFE, 0x38 };
IPAddress ip(192, 168, 2, 7);
EthernetServer server(99);

// Create aREST instance
aREST restRele = aREST();

void setup()
{
  Serial.begin(115200);
  startServer();
  startReleApi();
}

void startServer() {
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  // Start watchdog
  wdt_enable(WDTO_4S);
}

void startReleApi() {
  pinMode(RELE_0, OUTPUT);
  pinMode(RELE_1, OUTPUT);
  restRele.set_name("releAPI");
  restRele.set_id("2");
  restRele.function("releZero", releZeroControl);
  restRele.function("releOne", releOneControl);
}

void loop()
{
  EthernetClient client = server.available();
  restRele.handle(client);
  wdt_reset();
}

int releZeroControl(String command) {
  Serial.println(RELE_RECEIVE);
  int state = command.toInt();
  checkState(RELE_0, state);
  return state;
}

int releOneControl(String command) {
  Serial.println(RELE_RECEIVE);
  int state = command.toInt();
  checkState(RELE_1, state);
  return state;
}

void checkState(int pin , int state) {
  Serial.println(state);
  Serial.println(pin);
  if (state > 0) {
    Serial.println("HIGH");
    digitalWrite(pin, HIGH);
  }
  else {
    Serial.println("LOW");
    digitalWrite(pin, LOW);
  }
}





