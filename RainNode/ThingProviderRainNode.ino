#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

const int RAIN_D = 2; //Used to get rain sensor information
const int RAIN_A = A5; //Used to get rain sensor information
const String DIGITAL_MESSAGE_VALUE = "Digital value : ";
const String ANALOGIC_MESSAGE_VALUE = "Analogic value: ";
int digitalValue = 0;
int analogicValue = 0;

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
  startServer();
  startRainApi();
}

void loop()
{
  readDigitalPort();
  readAnalogicPort();
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

void readDigitalPort() {
  digitalValue = digitalRead(RAIN_D);
  Serial.println(DIGITAL_MESSAGE_VALUE);
  Serial.println(digitalValue);
}
void readAnalogicPort() {
  analogicValue = analogRead(RAIN_A);
  Serial.println(ANALOGIC_MESSAGE_VALUE);
  Serial.println(analogicValue);
}

void startRainApi() {
  pinMode(RAIN_D, INPUT);
  pinMode(RAIN_A, INPUT);
  //define the rest variables
  rest.variable("rainDigitalValue", &digitalValue);
  rest.variable("rainAnalogicValue", &analogicValue);
  rest.set_id("1");
  rest.set_name("rainAPI");
}
