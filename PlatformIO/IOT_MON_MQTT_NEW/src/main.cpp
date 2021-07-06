#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <string.h>

char ssidku[] = "BISMILLAH";     // diisi nama wifi
char password[] = "alhamdulillah"; // diisi password wifi

#define mqtt_port 1883
#define MQTT_USER "ghifari"
#define MQTT_PASSWORD "12345678"
#define PUBTOPICDEMO1 "/Pub_Data"
#define SUBTOPICDEMO1 "/Sub_Data"
#define USE_SERIAL Serial

const char* mqtt_server = "broker.hivemq.com"; //"m16.cloudmqtt.com";

char pub_str[100];

WiFiClient espClient;
PubSubClient client(espClient);
int Telegram_Delay = 2000;
int Time_Temp = 0;

int Pin_Led = D3;
int i = 0;
// send data serial
// double temp = 0; //variable konversi 10 bit ke 8 bit
// unsigned char tegangan = 0;
// unsigned char arus = 0;
// unsigned char daya = 0;
// unsigned char daya = 0;
// unsigned char status = 0;
// char *buffer;
String status_string = ""; 
// int sendTime = 0;
String bufferRx;
bool captureSerialRx = false;
bool completeSerialRx = false;
String strArusTerima;
String strDayaTerima;
String strStatusTerima;
uint16_t arusTerima = 0;
uint16_t dayaTerima = 0;
uint16_t status = 0;
uint16_t arusKirim = 0;

void kirim_pesan();
// read data serial
// char buffer[20];
// char daya_total[5];
// unsigned char data = 0;
// unsigned char kunci = 0;
// unsigned char checksum = 0;
void baca_pesan();


String ssid = ssidku;     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = password; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
uint8_t led = Pin_Led; 


void callback(char* topic, byte *payload, unsigned int length) {
    // Serial.println("-------new message from broker-----");
    // Serial.print("channel:");
    // Serial.println(topic);
    // if(topic == BROKERTOPIC1){
    arusKirim = *payload - '0';
    kirim_pesan();
    kirim_pesan();
      // Serial.print("get status data");
    // }
    // Serial.print("data:");  
    // Serial.write(payload, length);
    // Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      // Serial.println("connected");
      //Once connected, publish an announcement...
      client.subscribe(SUBTOPICDEMO1);
    } else {
      // Serial.print("failed, rc=");
      // Serial.print(client.state());
      // Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}

void publishSerialData(char *serialData, char* topic){
  if (!client.connected()) {
    reconnect();
//    Serial.println(" dc maneh\n");
  }
  client.publish(topic, serialData);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
	// Serial.println("Starting TelegramBot...");
  WiFi.begin(ssid, password);
  // pinMode(led, OUTPUT);
	// digitalWrite(led, HIGH);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect(); // turn off the led (inverted logic!)
}

void loop() {
  // put your main code here, to run repeatedly:
  baca_pesan();
  // sprintf(buffer,"%d%d%d%d%d",arus,daya_1,daya_2,daya_3,status);
  if(status == 0){
    status_string = "Safe";
  }
  else{
    status_string = "Trip";
  }
  if(!client.connected())
  {
    reconnect();
    // Serial.print("disconnected");
  }
  sprintf(pub_str,"\nArus = %s A \nDaya = %s W \nStatus = %s \n", strArusTerima, strDayaTerima, status_string);
  // Serial.print(pub_str);
  
  if(millis() - Time_Temp > Telegram_Delay){
    publishSerialData(pub_str, PUBTOPICDEMO1);
    Time_Temp = millis();
  }
  client.subscribe(SUBTOPICDEMO1);
  // char *boga = "\njalan\n";
  // publishSerialData(boga, WAFIQTOPICDEMO1);
  client.loop();
}

void kirim_pesan(){
  Serial.printf("B%dS", arusKirim);
  delay(4000);
  Serial.printf("B%dS", 0);
}

void baca_pesan(){
  if(Serial.available()){
    char rxChar = Serial.read();

    if(rxChar == 'A' && !captureSerialRx) captureSerialRx = true;
    else if(rxChar == 'S' && captureSerialRx) {
      captureSerialRx = false;
      completeSerialRx = true;
    }

    if(captureSerialRx) {
      bufferRx += rxChar;
    }
    // char *boga = "\njalan\n";
    // publishSerialData(boga, WAFIQTOPICDEMO1);
  }

  if(completeSerialRx){
    strArusTerima = bufferRx.charAt(1);
    strArusTerima += bufferRx.charAt(2);
    strArusTerima += bufferRx.charAt(3);
    strArusTerima += bufferRx.charAt(4);
    // arusTerima = strArusTerima.toInt();

    strDayaTerima = bufferRx.charAt(5);
    strDayaTerima += bufferRx.charAt(6);
    strDayaTerima += bufferRx.charAt(7);
    strDayaTerima += bufferRx.charAt(8);
    strDayaTerima += bufferRx.charAt(9);
    // if(strlen(strDayaTerima.c_str()) == 3) dayaTerima = strDayaTerima.toInt();
    strStatusTerima = bufferRx.charAt(10);
    status = strStatusTerima.toInt();
    bufferRx = "";
    completeSerialRx = false;
  }
}