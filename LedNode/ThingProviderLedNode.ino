#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

const int ledPin = 7; //Used to get rain sensor information
//Ethernet configuration
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };
// IP address
IPAddress ip(192, 168, 2, 2);
// Ethernet server
EthernetServer server(98);

// Create aREST instance
aREST rest = aREST();

void setup()
{
  Serial.begin(115200);
  startLedApi();
  startServer();
}

void loop()
{
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
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
void startLedApi() {
  rest.set_name("ledAPI");
  rest.set_id("2");
  rest.function("led", ledControl);
}

int ledControl(String command) {
  int state = command.toInt();
  digitalWrite(ledPin, state);
  return 1;
}
