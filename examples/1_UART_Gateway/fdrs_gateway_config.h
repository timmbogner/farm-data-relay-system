//  FARM DATA RELAY SYSTEM
//
//  GATEWAY CONFIGURATION

//Addresses
#define UNIT_MAC           0x01  // The address of this gateway

#define ESPNOW_NEIGHBOR_1  0x00  // Address of ESP-NOW neighbor #1
#define ESPNOW_NEIGHBOR_2  0x02  // Address of ESP-NOW neighbor #2
#define LORA_NEIGHBOR_1    0x00  // Address of LoRa neighbor #1
#define LORA_NEIGHBOR_2    0x03  // Address of LoRa neighbor #2

// Interfaces
#define USE_ESPNOW  
//#define USE_LORA
//#define USE_WIFI  // Will cause errors if used with ESP-NOW. Use a serial link instead!
//#define USE_ETHERNET

// Routing
// Options: sendESPNowNbr(1 or 2); sendESPNowPeers(); sendLoRaNbr(1 or 2); broadcastLoRa(); sendSerial(); sendMQTT();
#define ESPNOWG_ACT    sendSerial();
#define LORAG_ACT      sendSerial();
#define SERIAL_ACT     sendESPNowNbr(2); sendESPNowPeers(); sendLoRaNbr(2); broadcastLoRa(); 
#define MQTT_ACT          
#define INTERNAL_ACT   sendSerial();
#define ESPNOW1_ACT    
#define ESPNOW2_ACT    sendSerial();                
#define LORA1_ACT      
#define LORA2_ACT      sendSerial();

// LoRa Configuration
#define RADIOLIB_MODULE SX1276
#define LORA_SS    18
#define LORA_RST   14
#define LORA_DIO   26
#define LORA_BUSY  33
//#define USE_SX126X

#define LORA_TXPWR 17   // LoRa TX power in dBm (: +2dBm - +17dBm (for SX1276-7) +20dBm (for SX1278))

//#define CUSTOM_SPI
#define LORA_SPI_SCK  5
#define LORA_SPI_MISO 19
#define LORA_SPI_MOSI 27

#define FDRS_DEBUG     // Enable USB-Serial debugging

// OLED -- Displays console debugging messages on an SSD1306 I²C OLED
///#define USE_OLED    
#define OLED_HEADER "FDRS"
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16

// UART data interface pins (if available)
#define RXD2 14
#define TXD2 15

//#define USE_LR  // Use ESP-NOW LR mode (ESP32 only)

// WiFi and MQTT Credentials  -- These will override the global settings
//#define WIFI_SSID     "Your SSID"  
//#define WIFI_PASS     "Your Password"
//#define DNS_IPADDRESS "192.168.0.1"     // Valid DNS IP address.  If not known, try "8.8.8.8"

//#define MQTT_ADDR   "192.168.0.8"
//#define MQTT_PORT   1883 // Default MQTT port is 1883
//#define MQTT_AUTH   //Enable MQTT authentication 
//#define MQTT_USER   "Your MQTT Username"
//#define MQTT_PASS   "Your MQTT Password"

// NTP Time settings
//#define TIME_SERVER       "0.us.pool.ntp.org"       // NTP time server to use. If FQDN at least one DNS server is required to resolve name
//#define LOCAL_OFFSET      (-6)                     // Local time offset in hours from UTC - if unsure, check https://time.is
//#define TIME_FETCHNTP     15      // Time in minutes between fetching time from NTP server
//#define TIME_PRINTTIME    10      // Time in minutes between printing local time
