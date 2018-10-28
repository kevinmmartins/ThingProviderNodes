#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

// LDR Pins
const int LDR_0 = A0;
const int LDR_1 = A1;
const int LDR_2 = A2;

// Messages
const String LDR_ZERO_MESSAGE = "LDR Zero value : ";
const String LDR_ONE_MESSAGE = "LDR One value : ";
const String LDR_TWO_MESSAGE = "LDR Two value : ";

// Variables to save info
int ldrZeroValue = 0;
int ldrOneValue = 0;
int ldrTwoValue = 0;

//Ethernet configuration
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };
IPAddress ip(192, 168, 2, 2);
EthernetServer server(98);

// Create aREST instance
aREST restLdr = aREST();

void setup()
{
  Serial.begin(115200);
  startServer();
  startLdrApi();
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

void startLdrApi() {
  pinMode(LDR_0, INPUT);
  pinMode(LDR_1, INPUT);
  pinMode(LDR_2, INPUT);
  //define the rest variables
  restLdr.variable("ldrZero", &ldrZeroValue);
  restLdr.variable("ldrOne", &ldrOneValue);
  restLdr.variable("ldrTwo", &ldrTwoValue);
  restLdr.set_id("1");
  restLdr.set_name("ldrAPI");
}

void loop()
{
  readAnalogicPortLdrZero();
  readAnalogicPortLdrOne();
  readAnalogicPortLdrTwo();
  EthernetClient client = server.available();
  restLdr.handle(client);
  wdt_reset();
}

void readAnalogicPortLdrZero() {
  delay(1000);
  ldrZeroValue = analogRead(LDR_0);
  Serial.println(LDR_ZERO_MESSAGE);
  Serial.println(ldrZeroValue);
}

void readAnalogicPortLdrOne() {
  delay(1000);
  ldrOneValue = analogRead(LDR_1);
  Serial.println(LDR_ONE_MESSAGE);
  Serial.println(ldrOneValue);
}

void readAnalogicPortLdrTwo() {
  delay(1000);
  ldrTwoValue = analogRead(LDR_2);
  Serial.println(LDR_TWO_MESSAGE);
  Serial.println(ldrTwoValue);
}


