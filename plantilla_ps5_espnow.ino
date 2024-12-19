#include <Bluepad32.h>
#include <esp_now.h>
#include <WiFi.h>

static int led = 4;

int CH1_VAL=0;
int CH2_VAL=0;

#define JOYSTICK_DEADZONE (30);
int CH_1= 0 ; // Y
int CH_2= 0 ; // X
int CH_3= 0 ; // POT
int CH_4= 0 ; // Y DER
int CH_5= 0 ; // X DER
int CH_6= 0 ; // POT tilt

//Valores map
const int minCH1 = 512, medCH1 = 8, maxCH1 = -508; 
const int minCH2 = -508, medCH2 = 8, maxCH2 = 512; 
const int minCH4 = 512, medCH4 = 4, maxCH4 = -508; 
const int minCH5 = -508, medCH5 = 4, maxCH5 = 512;

const int deadRangeLowCH1  = medCH1+JOYSTICK_DEADZONE; 
const int deadRangeHighCH1 = medCH1-JOYSTICK_DEADZONE;
const int deadRangeLowCH2  = medCH2-JOYSTICK_DEADZONE; 
const int deadRangeHighCH2 = medCH2+JOYSTICK_DEADZONE; 
const int deadRangeLowCH4  = medCH4+JOYSTICK_DEADZONE; 
const int deadRangeHighCH4 = medCH4-JOYSTICK_DEADZONE; 
const int deadRangeLowCH5  = medCH5-JOYSTICK_DEADZONE; 
const int deadRangeHighCH5 = medCH5+JOYSTICK_DEADZONE; 

const int minMap = -100, maxMap = 100;


// clientes
uint8_t broadcastAddress1[] = {0x30, 0xC9, 0x22, 0xB0, 0x2F, 0x88};  //waveshare robot
uint8_t broadcastAddress2[] = {0x34, 0x5F, 0x45, 0xA7, 0x94, 0xE0};  //Pantalla mando sobremesa
uint8_t broadcastAddress3[] = {0xA4, 0xCF, 0x12, 0xED, 0x88, 0xCC};  //mini pantalla
uint8_t broadcastAddress4[] = {0x64, 0xE8, 0x33, 0x7C, 0xB2, 0x04};  //PANTALLA 7" WAVESHARE


typedef struct data_struct {
  int CH1; // CH1
  int CH2; // CH2
  int CH3; // CH3
  int CH4; // CH4
  int CH5; // CH5
  int CH6; // CH6

  byte switch7Value;  // CH7
  byte switch8Value;  // CH8
  byte switch9Value;  // CH9
  byte switch10Value; // CH10
  byte switch11Value; // CH11
  byte switch12Value; // CH12
  byte switch13Value; // CH13
  byte switch14Value; // CH14
  byte switch15Value; // CH15
  byte switch16Value; // CH16
} data_struct;

data_struct data;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //char macStr[18];
  //Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  //         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //Serial.print(macStr);
  //Serial.print(" send status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}




ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// ========= GAME CONTROLLER ACTIONS SECTION ========= //

void processGamepad(ControllerPtr ctl) {
/*
int v1 = 25; 
if (v1 < deadRangeLowCH1) CH_1= (map(v1,minCH1,deadRangeLowCH1,-100,0));
else if (v1 > deadRangeHighCH1){ CH_1= (map(v1,deadRangeHighCH1,maxCH1,0,100));}  //OK
else{CH_1= 0;}
data.CH1 = CH_1;

int v2 = 25; 
if (v2 < deadRangeLowCH2) CH_2= (map(v2,minCH2,deadRangeLowCH2,-100,0));
else if (v2 > deadRangeHighCH2){ CH_2= (map(v2,deadRangeHighCH2,maxCH2,0,100));}
else{CH_2= 0;}
data.CH2 = CH_2;

data.CH3 = ctl->brake();

int v4 = 25; 
if (v4 < deadRangeLowCH4) CH_4= (map(v4,deadRangeLowCH4,minCH4,0,-120));  
else if (v4 > deadRangeHighCH4){ CH_4= (map(v4,maxCH4,deadRangeHighCH4,120,0));} 
else{CH_4= 0;}
data.CH4 = CH_4;

int v5 = 25; 
if (v5 < deadRangeLowCH5) CH_5= (map(v5,deadRangeLowCH5,minCH5,0,-106)); 
else if (v5 > deadRangeHighCH5){ CH_5= (map(v5,maxCH5,deadRangeHighCH5,127,0));}  //OK
else{CH_5= 0;}
data.CH5 = CH_5;

int v6 = ctl->throttle(); 
CH_6= (map(v6,0,1020,0,100));
data.CH6 = CH_6;

*/
int v1 = ctl->axisY(); 
if (v1 > deadRangeLowCH1) CH_1= (map(v1,minCH1,deadRangeLowCH1,-100,0));
else if (v1 < deadRangeHighCH1){ CH_1= (map(v1,deadRangeHighCH1,maxCH1,0,100));}  //OK
else{CH_1= 0;}
data.CH1 = CH_1;

int v2 = ctl->axisX(); 
if (v2 < deadRangeLowCH2) CH_2= (map(v2,minCH2,deadRangeLowCH2,-100,0));
else if (v2 > deadRangeHighCH2){ CH_2= (map(v2,deadRangeHighCH2,maxCH2,0,100));}
else{CH_2= 0;}
data.CH2 = CH_2;

int v3 = ctl->brake(); 
CH_3= (map(v3,0,1020,0,100));
data.CH3 = CH_3;


int v4 = ctl->axisRY(); 
if (v4 > deadRangeLowCH4) CH_4= (map(v4,minCH4,deadRangeLowCH4,-100,0));
else if (v4 < deadRangeHighCH4){ CH_4= (map(v4,deadRangeHighCH4,maxCH4,0,100));}  //OK
else{CH_4= 0;}
data.CH4 = CH_4;

int v5 = ctl->axisRX(); 
if (v5 < deadRangeLowCH5) CH_5= (map(v5,minCH5,deadRangeLowCH5,-100,0));
else if (v5 > deadRangeHighCH5){ CH_5= (map(v5,deadRangeHighCH5,maxCH5,0,100));}
else{CH_5= 0;}
data.CH5 = CH_5;

int v6 = ctl->throttle(); 
CH_6= (map(v6,0,1020,0,100));
data.CH6 = CH_6;

if (ctl->buttons() == 0x0001) {  // X
data.switch7Value   = 1;
  }
if (ctl->buttons() != 0x0001) {
data.switch7Value   = 0;
  }

if (ctl->buttons() == 0x0002) {  // 0
data.switch8Value   = 1;
  }
if (ctl->buttons() != 0x0002) {
data.switch8Value   = 0;
  }

if (ctl->buttons() == 0x0008) {  // ^
data.switch9Value   = 1;
  }
if (ctl->buttons() != 0x0008) {
data.switch9Value   = 0;
  }

if (ctl->buttons() == 0x0004) {  // []
data.switch10Value   = 1;
  }
if (ctl->buttons() != 0x0004) {
data.switch10Value   = 0;
  }      

if (ctl->buttons() == 0x0010) {  // L1
data.switch11Value   = 1;
  }
if (ctl->buttons() != 0x0010) {
data.switch11Value   = 0;
  }  

if (ctl->buttons() == 0x0020) {  // R1
data.switch12Value   = 1;
  }
if (ctl->buttons() != 0x0020) {
data.switch12Value   = 0;
  }    

if (ctl->buttons() == 0x0100) {  // JOY L
data.switch13Value   = 1;
  }
if (ctl->buttons() != 0x0100) {
data.switch13Value   = 0;
  }  
  if (ctl->buttons() == 0x0200) {  // JOY R
data.switch14Value   = 1;
  }
if (ctl->buttons() != 0x0200) {
data.switch14Value   = 0;
  }  

  esp_err_t result = esp_now_send(0, (uint8_t *) &data, sizeof(data_struct));
   
  if (result == ESP_OK) {
    //analogWrite(2,5);
  }
  else {
    //analogWrite(2,0);
  }
}


// Arduino setup function. Runs in CPU 1
void setup() {
  //Serial.begin(115200);
  //Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  //Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Setup the Bluepad32 callbacks
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But it might also fix some connection / re-connection issues.
  //BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);

  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  // register peer
registrar_clientes();  
}

// Arduino loop function. Runs in CPU 1.
void loop() {

  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();

//vTaskDelay(1);
delay(110);

}