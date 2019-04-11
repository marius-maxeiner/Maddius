

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WSout 5  // Pin D1
#define WSbit (1<<WSout)

// ARTNET CODES
#define ARTNET_DATA 0x50
#define ARTNET_POLL 0x20
#define ARTNET_POLL_REPLY 0x21
#define ARTNET_PORT 6454
#define ARTNET_HEADER 17

// Button
#define modeSelect 2  // D4 Pin
#define saveMode 0  // D3 Pin



WiFiUDP udp;

uint8_t uniData[510];
uint16_t uniSize;
uint8_t hData[ARTNET_HEADER + 1];
uint8_t net = 0;
uint8_t universe = 22;
uint8_t subnet = 0;

// Mode
uint8_t ledMode = 0;
uint8_t lastLedMode = 0;

uint8_t modeData[7][510];

// WPA

//const char* ssid     = "FRITZ!Box 7490";
//const char* password = "85489645769472290977";

const char* ssid     = "Jazzkeller Intern";
const char* password = "ZTS745cccaaa6328w35TR";

// const char* ssid     = "Haus der Jugend";
// const char* password = "Rahmschnitzel";

IPAddress local_ip(192, 168, 1, 234);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_ip(255, 255, 255, 0);

void setup() {
   //
   pinMode(WSout, OUTPUT);

  
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("set first Light");
  for(int a; a != 3  ;a++){
    sendFirst(); 
  }



  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // pinMode(modeSelect, INPUT);
  // digitalWrite(modeSelect, HIGH);

  WiFi.begin(ssid, password);
  WiFi.config(local_ip, gateway_ip, subnet_ip);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  

  udp.begin(ARTNET_PORT); // Open ArtNet port

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendFirst() {
  delay(1000);
  Serial.print(".");
  for(uint16_t i = 0; i < uniSize; i++){
    if((i+1)%4 == 0){
      uniData[i] = 255;
    } else {
      uniData[i] = 0;
    }
  }
  uniSize = 144;
  sendWS();
}

void sendWS() {
  uint32_t writeBits;
  uint8_t  bitMask, time;
  os_intr_lock();
  for (uint16_t t = 0; t < uniSize; t++) { // outer loop counting bytes
    bitMask = 0x80;
    while (bitMask) {
      // time=0ns : start by setting bit on
      time = 4;
      while (time--) {
        WRITE_PERI_REG( 0x60000304, WSbit );  // do ON bits // T=0
      }
      if ( uniData[t] & bitMask ) {
        writeBits = 0;  // if this is a '1' keep the on time on for longer, so dont write an off bit
      }
      else {
        writeBits = WSbit;  // else it must be a zero, so write the off bit !
      }
      time = 4;
      while (time--) {
        WRITE_PERI_REG( 0x60000308, writeBits );  // do OFF bits // T='0' time 350ns
      }
      time = 6;
      while (time--) {
        WRITE_PERI_REG( 0x60000308, WSbit );  // switch all bits off  T='1' time 700ns
      }
      // end of bite write time=1250ns
      bitMask >>= 1;
    }
  }
  os_intr_unlock();
}

void loop() {
  

  
 /*if(digitalRead(modeSelect) == LOW){
    if(ledMode == lastLedMode){
      ledMode = ledMode + 1;
      Serial.print("mode:");
      Serial.println(ledMode);
    }
  } else {
    lastLedMode = ledMode;
  }
  if(ledMode == 8){
    ledMode = 0;
  }

  if(ledMode > 0){
    if(digitalRead(saveMode) == LOW){
      memcpy(modeData[ledMode - 1], uniData, 510);
      Serial.print("save mode:");
      Serial.println(ledMode);
    } else {
      uniSize = 510;
      memcpy(uniData, modeData[ledMode - 1], 510);
      sendWS();
    }
  }*/

  if (udp.parsePacket()) {
    udp.read(hData, ARTNET_HEADER + 1);
    if ( hData[0] == 'A' && hData[1] == 'r' && hData[2] == 't' && hData[3] == '-' && hData[4] == 'N' && hData[5] == 'e' && hData[6] == 't') {
      if ( hData[8] == 0x00 && hData[9] == ARTNET_DATA && hData[15] == net ) {
        if ( hData[14] == (subnet << 4) + universe ) { // UNIVERSE
          uniSize = (hData[16] << 8) + (hData[17]);
          udp.read(uniData, uniSize);
          Serial.print("ArtNet packet RX Uni:");
          Serial.print(universe);
          Serial.print(" - size:");
          Serial.println(uniSize);
          sendWS();
        }
      } // if Artnet Data
    }
  }
}
