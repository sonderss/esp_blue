#include <Arduino.h>
#include <BluetoothSerial.h>
// #include <BLEDevice.h>
BluetoothSerial SerialBT;

int state = 0;
int RGB_Blue = 2;
int RGB_RED = 4;
int RGB_GREEN = 15;

void setup()
{
  Serial.begin(115200);
  // BLEDevice::init("ESP32BLE");
  SerialBT.begin("SONDER_xiaomi"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
  SerialBT.setPin("1234");         // 蓝牙连接的配对码
  Serial.printf("BT initial ok and ready to pair. \r\n");
  pinMode(RGB_RED, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    // Serial.write(SerialBT.read());
    state = SerialBT.read();
    // int inByte = SerialBT.read();
    // char user = (char)inByte;
    if (state == '1')
    {
      Serial.printf("flash light \r\n");
      // Serial.write("%d \n", state_txt);
      digitalWrite(RGB_RED, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(1000);                 // wait for a second
      digitalWrite(RGB_RED, LOW);  // turn the LED off by making the voltage LOW
      delay(1000);
    }
    if (state == '2')
    {
      Serial.printf("turn on \r\n");
      digitalWrite(RGB_RED, HIGH); // turn the LED on (HIGH is the voltage level)
    }
    if (state == '0')
    {
      Serial.printf("turn off \r\n");
      digitalWrite(RGB_RED, LOW); // turn the LED on (HIGH is the voltage level)
    }
  }
  delay(1);
}

// #include <Arduino.h>
// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>
// #include <BLE2902.h>

// BLECharacteristic *pCharacteristic;
// bool deviceConnected = false;
// uint8_t txValue = 0;

// // See the following for generating UUIDs:
// // https://www.uuidgenerator.net/

// #define SERVICE_UUID           "4b8c1274-38d0-11ec-8d3d-0242ac130003" // UART service UUID
// #define CHARACTERISTIC_UUID_RX "4b8c1274-38d0-11ec-8d3d-0242ac130003"
// #define CHARACTERISTIC_UUID_TX "4b8c1274-38d0-11ec-8d3d-0242ac130003"

// class MyServerCallbacks: public BLEServerCallbacks {
//     void onConnect(BLEServer* pServer) {
//       deviceConnected = true;
//     };

//     void onDisconnect(BLEServer* pServer) {
//       deviceConnected = false;
//     }
// };

// class MyCallbacks: public BLECharacteristicCallbacks {
//     void onWrite(BLECharacteristic *pCharacteristic) {
//       std::string rxValue = pCharacteristic->getValue();

//       if (rxValue.length() > 0) {
//         Serial.println("*********");
//         Serial.print("Received Value: ");
//         for (int i = 0; i < rxValue.length(); i++)
//           Serial.print(rxValue[i]);

//         Serial.println(

//         );
//         Serial.println("*********");
//       }
//     }
// };

// void setup() {
//   Serial.begin(115200);

//   // Create the BLE Device
//   BLEDevice::init("ESP32BLE");

//   // Create the BLE Server
//   BLEServer *pServer = BLEDevice::createServer();
//   pServer->setCallbacks(new MyServerCallbacks());

//   // Create the BLE Service
//   BLEService *pService = pServer->createService(SERVICE_UUID);

//   // Create a BLE Characteristic
//   pCharacteristic = pService->createCharacteristic(
//                       CHARACTERISTIC_UUID_TX,
//                       BLECharacteristic::PROPERTY_NOTIFY
//                     );
//   pCharacteristic->addDescriptor(new BLE2902());

//   BLECharacteristic *pCharacteristic = pService->createCharacteristic(
//                                          CHARACTERISTIC_UUID_RX,
//                                          BLECharacteristic::PROPERTY_WRITE
//                                        );

//   pCharacteristic->setCallbacks(new MyCallbacks());

//   // Start the service
//   pService->start();

//   // Start advertising
//   pServer->getAdvertising()->start();
//   Serial.println("Waiting a client connection to notify...");
// }

// void loop() {

//   if (deviceConnected) {
//     Serial.printf("*** Sent Value: %d ***\n", txValue);
//     pCharacteristic->setValue(&txValue, 1);
//     pCharacteristic->notify();
//     txValue++;
//   }
//   delay(1000);
// }