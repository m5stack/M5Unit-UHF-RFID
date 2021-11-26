// #include <M5Stack.h>
// #include "M5GFX.h"

// #define TINY_GSM_MODEM_SIM7080

// // Set serial for debug console (to the Serial Monitor, default speed 115200)
// #define SerialMon Serial
// #define SerialAT Serial2

// #define TINY_GSM_RX_BUFFER 650

// #define TINY_GSM_DEBUG SerialMon

// #define GSM_AUTOBAUD_MIN 115200
// #define GSM_AUTOBAUD_MAX 115200

// // #define GSM_AUTOBAUD_MIN 9600
// // #define GSM_AUTOBAUD_MAX 115200

// #define TINY_GSM_USE_GPRS true
// #define TINY_GSM_USE_WIFI false

// #define GSM_PIN ""

// // Your GPRS credentials, if any
// const char apn[]      = "YourAPN";
// const char gprsUser[] = "";
// const char gprsPass[] = "";

// // Your WiFi connection credentials, if applicable
// const char wifiSSID[] = "YourSSID";
// const char wifiPass[] = "YourWiFiPass";

// // Server details
// const char server[]   = "www.baidu.com";
// const char resource[] = "/";

// #include <TinyGsmClient.h>

// // Just in case someone defined the wrong thing..
// #if TINY_GSM_USE_GPRS && not defined TINY_GSM_MODEM_HAS_GPRS
// #undef TINY_GSM_USE_GPRS
// #undef TINY_GSM_USE_WIFI
// #define TINY_GSM_USE_GPRS false
// #define TINY_GSM_USE_WIFI true
// #endif
// #if TINY_GSM_USE_WIFI && not defined TINY_GSM_MODEM_HAS_WIFI
// #undef TINY_GSM_USE_GPRS
// #undef TINY_GSM_USE_WIFI
// #define TINY_GSM_USE_GPRS true
// #define TINY_GSM_USE_WIFI false
// #endif

// #ifdef DUMP_AT_COMMANDS
// #include <StreamDebugger.h>
// StreamDebugger debugger(SerialAT, SerialMon);
// TinyGsm        modem(debugger);
// #else
// TinyGsm        modem(SerialAT);
// #endif

// #ifdef USE_SSL
// TinyGsmClientSecure client(modem);
// const int           port = 443;
// #else
// TinyGsmClient  client(modem);
// const int      port = 80;
// #endif

// M5GFX display;
// M5Canvas canvas(&display);

// unsigned long start;

// inline String time() {
//   return "..."+String((millis()-start)/1000)+'s';
// }

// void setup() {
//   M5.begin();
//   display.begin();
//   start = millis();
//   canvas.setColorDepth(1); // mono color
//   canvas.setFont(&fonts::efontCN_14);
//   canvas.createSprite(display.width(), display.height());
//   canvas.setTextSize(2);
//   canvas.setPaletteColor(1, GREEN);
//   canvas.setTextScroll(true);
//   SerialMon.println("Wait...");

//   canvas.println("初始化模块"+time());
//   canvas.pushSprite(0, 0);
//   // Set GSM module baud rate
//   if(TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX) == 0) {
//     canvas.println("串口连接失败，请检查连接"+time());
//   }
//   // SerialAT.begin(9600);


//   // Restart takes quite some time
//   // To skip it, call init() instead of restart()
//   SerialMon.println("Initializing modem...");
//   modem.restart();
//   // modem.init();

//   String modemInfo = modem.getModemInfo();
//   SerialMon.print("Modem Info: ");
//   SerialMon.println(modemInfo);
//   canvas.println(modemInfo+time());
//   canvas.pushSprite(0, 0);

//   while(!modem.getSimStatus()) {
//     canvas.println("未检测到SIM卡"+time());
//     canvas.pushSprite(0, 0);
//   }

// #if TINY_GSM_USE_GPRS
//   // Unlock your SIM card with a PIN if needed
//   if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }
// #endif
// }

// void loop() {

//   SerialMon.print("Waiting for network...");
//   canvas.println("搜寻网络...."+time());
//   canvas.pushSprite(0, 0);

//   if (!modem.waitForNetwork()) {
//     SerialMon.println(" fail");
//     delay(10000);
//     return;
//   }
//   SerialMon.println(" success");

//   if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }

// #if TINY_GSM_USE_GPRS
//   // GPRS connection parameters are usually set after network registration
//   SerialMon.print(F("Connecting to "));
//   canvas.println("开始连接网络..."+time());
//   canvas.pushSprite(0, 0);
//   SerialMon.print(apn);
//   if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//     SerialMon.println(" fail");
//     canvas.println("连接失败..."+time());
//     canvas.pushSprite(0, 0);
//     delay(10000);
//     return;
//   }
//   SerialMon.println(" success");
//   if (modem.isGprsConnected()) { SerialMon.println("GPRS connected"); }
// #endif
//   canvas.println("连接成功..."+time());

//   SerialMon.println(" success");

//   String ccid = modem.getSimCCID();
//   SerialMon.print("CCID: ");
//   SerialMon.println(ccid);

//   String imei = modem.getIMEI();
//   SerialMon.print("IMEI: ");
//   SerialMon.println(imei);

//   String imsi = modem.getIMSI();
//   SerialMon.print("IMSI: ");
//   SerialMon.println(imsi);

//   String cop = modem.getOperator();
//   SerialMon.print("Operator: ");
//   SerialMon.println(cop);

//   IPAddress local = modem.localIP();
//   SerialMon.print("REMOTE IP: ");
//   SerialMon.println(local.toString());

//   int csq = modem.getSignalQuality();
//   SerialMon.printf("Signal quality: %d \r\n", csq);

//   canvas.println("信号RSSI:"+String(csq)+time());
//   canvas.println("IP:"+local.toString()+time());
//   canvas.println("测试通过"+time());
//   canvas.pushSprite(0, 0);


//   modem.gprsDisconnect();

//   SerialMon.println(F("GPRS disconnected"));

//   // Do nothing forevermore

//   canvas.println("按下B键继续测试GPS"+time());
//   canvas.pushSprite(0, 0);

//   while (true) {
//       M5.update();
//       if(M5.BtnB.wasPressed()){
//           break;
//       }
//   }
 
//   canvas.println("开始测试GPS"+time());
//   canvas.pushSprite(0, 0);

//   while (1)
//   {
//     DBG("Enabling GPS/GNSS/GLONASS and waiting 15s for warm-up");
//     modem.enableGPS();
//     delay(15000L);
//     float lat2      = 0;
//     float lon2      = 0;
//     float speed2    = 0;
//     float alt2      = 0;
//     int   vsat2     = 0;
//     int   usat2     = 0;
//     float accuracy2 = 0;
//     int   year2     = 0;
//     int   month2    = 0;
//     int   day2      = 0;
//     int   hour2     = 0;
//     int   min2      = 0;
//     int   sec2      = 0;
//     for (int8_t i = 15; i; i--) {
//         DBG("Requesting current GPS/GNSS/GLONASS location");
//         if (modem.getGPS(&lat2, &lon2, &speed2, &alt2, &vsat2, &usat2, &accuracy2,
//                         &year2, &month2, &day2, &hour2, &min2, &sec2)) {
//         DBG("Latitude:", String(lat2, 8), "\tLongitude:", String(lon2, 8));
//         DBG("Speed:", speed2, "\tAltitude:", alt2);
//         DBG("Visible Satellites:", vsat2, "\tUsed Satellites:", usat2);
//         DBG("Accuracy:", accuracy2);
//         DBG("Year:", year2, "\tMonth:", month2, "\tDay:", day2);
//         DBG("Hour:", hour2, "\tMinute:", min2, "\tSecond:", sec2);
//         break;
//         } else {
//         DBG("Couldn't get GPS/GNSS/GLONASS location, retrying in 15s.");
//         delay(15000L);
//         }
//     }
//     DBG("Retrieving GPS/GNSS/GLONASS location again as a string");
//     String gps_raw = modem.getGPSraw();
//     DBG("GPS/GNSS Based Location String:", gps_raw);
//     DBG("Disabling GPS");
//     modem.disableGPS();
//   }
// }




#include <M5Stack.h>
#include "UNIT_UHF_RFID.h"

JRD_4035 uhf;

void setup() {
  M5.begin(); //Init M5Core.  初始化 M5Core
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  // uhf.begin(HardwareSerial *serial = &Serial2, int baud=115200, uint8_t RX = 16, uint8_t TX = 17, bool debug = false);
  uhf.begin(&Serial2, 115200, 16, 17, false);
//   uhf.begin();
  while(1){
    String version = uhf.getVersion();
    if(version != "ERROR"){
      Serial.println(version);
      break;
    }
  }
}

uint8_t write_buffer[] = {0xab, 0xcd, 0xef, 0xdd};  
uint8_t reade_buffer[4] = {0};

//1. Polling Card EPC
//2. Select Card EPC
//3. Write or Read Card Info

void loop() {
    if(M5.BtnA.wasPressed()){
        Serial.println("Write Data...");
        //uhf.writeCard(uint8_t *data, size_t size, uint8_t membank, uint16_t sa, uint32_t access_password = 0);
        if(uhf.writeCard(write_buffer, sizeof(write_buffer), 0x04, 0, 0x00000000)){
          Serial.println("Write OK");
        }else{
          Serial.println("Write ERROR");
        }
        delay(1000);
        Serial.println("Read Data...");
        //uhf.readCard(uint8_t *data, size_t size, uint8_t membank, uint16_t sa, uint32_t access_password = 0);
        if(uhf.readCard(reade_buffer, sizeof(reade_buffer), 0x04, 0, 0x00000000)){
          Serial.println("Read OK");
          Serial.println("Data Content");
          for (uint8_t i = 0; i < sizeof(reade_buffer); i++)
          {
            Serial.printf("%x", reade_buffer[i]);
          }
        }else{
          Serial.println("Read ERROR");
        }
    }
    if(M5.BtnB.wasPressed()){
        Serial.println("polling once");
        uint8_t result = uhf.pollingOnce();
        // polling 10 times
        // uint8_t result = uhf.pollingMultiple(20);
        Serial.printf("scan result: %d\r\n", result);
        if(result>0){
          for(uint8_t i=0; i<result; i++){
              Serial.println("pc: "+ uhf.cards[i].pc_str);
              Serial.println("rssi: "+ uhf.cards[i].rssi_str);
              Serial.println("epc: "+ uhf.cards[i].epc_str);
              Serial.println("-----------------------");
              delay(10);
          }
        }
    }
    if(M5.BtnC.wasPressed()){
        if(uhf.select(uhf.cards[0].epc)){
          Serial.println("Select OK");
        }else{
          Serial.println("Select ERROR");
        }
        Serial.println("Current Select EPC:");
        Serial.println(uhf.selectInfo());
    }
    M5.update();
}