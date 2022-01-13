/*  NETPIE ESP8266 basic sample                            */
/*  More information visit : https://netpie.io             */

#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <Wire.h>
#include <SPI.h>
const char* ssid     = "IPcam";
const char* password = "12345678";

#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define APPID   "RobotCarEEE"
#define KEY     "ytTiLr96001CS7E"
#define SECRET  "Sx7pxAKVUqzBsWC5cd6qzSU1a"
#define ALIAS   "esp8266"

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

int sensitive = 66; // สำหรับ 30A
// int sensitive = 100; // สำหรับ 20A
// int sensitive = 185; // สำหรับ 5A
int offset = 2525; // ค่าเริ่มต้น 2500 ปรับค่าตรงนี้เพื่อให้ค่ายังไม่มีโหลดเป็น 0.00

volatile byte pulses; // number of pulses
unsigned long timeold;
unsigned int rpm;
unsigned int pulsesperturn = 12;
int interruptPin = D6;

long previousMillis = 0;
long interval = 2000;
int a = 60;

unsigned long delayTime;

const int pingPin = D8;
int inPin = D7;

int Motor1  = D1;
int Motor2  = D2;
int Motor3  = D3;
int Motor4  = D4;
unsigned status;
/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  String top = (String)topic;
  msg[msglen] = '\0';
  String message = (String)(char *)msg;
  Serial.print(top);
  Serial.print(" ");
  Serial.println(message);
  if (top == "/RobotCarEEE/RobotCar/car") {
    if (message == "forward") {
      forward();
    } else if (message == "reward") {
      reward();
    } else if (message == "left") {
      left();
    } else if (message == "right") {
      right();
    } else if (message == "stop") {
      stop();
    } else {
      stop();
    }
  }

}


/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");

  microgear.setAlias(ALIAS);
  microgear.subscribe("/RobotCar/+");
}


void setup() {


  dht.begin();
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Motor3, OUTPUT);
  pinMode(Motor4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Starting...");
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* Initial with KEY, SECRET and also set the ALIAS here */
  microgear.init(KEY, SECRET, ALIAS);

  /* connect to NETPIE to a specific APPID */
  microgear.connect(APPID);
}

void loop() {
  /* To check if the microgear is still connected */
  float li =  Ultrasonic();
  float Amp = sensorAmp();
  float hum =  DHThum();
  unsigned long currentMillis = millis();

if (currentMillis - previousMillis > interval) {
 previousMillis = currentMillis;
if(digitalWrite(interruptPin)==1){
 pulses++;
  if (millis() - timeold >= 1000) {
    rpm = (60 * 1000 / pulsesperturn ) / (millis() - timeold) * pulses;
    timeold = millis();
    pulses = 0;
  } 
}

  
}else {
 Serial.print("Analog Value =");
  Serial.println(rpm);
}
   wild_speed();
  if (microgear.connected()) {

    /* Call this method regularly otherwise the connection may be lost */
    microgear.loop();

    if (timer >= 5000) {
      String all = "" ;
      
        all += (String)hum +"," +Amp+"," +rpm+"," +li;
      

      microgear.publish("/RobotCar/all" , all);

      timer = 0;
    }
    else timer += 100;
  }
  else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);
}
