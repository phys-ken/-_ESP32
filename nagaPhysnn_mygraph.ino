
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required l ibraries

  #include <WiFi.h>
#include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
  #include <Wire.h>


AsyncWebServer server(80);

// wifiアクセスポイントの名前・パスワードを設定
const char ssid[] = "nagaPhys04";  // SSID
const char pass[] = "11241124";   // password

const IPAddress ip(192, 168, 20, 2);      // IPアドレス
const IPAddress subnet(255, 255, 255, 0); // サブネットマスク



//距離の測定関数の定義（フィルターなし）
String readHCSR04cm() {
 int Echo = 14;  // Echoピン
 int Trig = 15;  // Trigピン


  // ピン設定
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // trigger
  digitalWrite(Trig, HIGH);
  delay(20); // msec
  digitalWrite(Trig, LOW);

  // echo
  int intervalUS = pulseIn(Echo, HIGH) / 2;   // 超音波の往復の時間を2で割って片道の時間（単位：μsec）にする

  // 時間を距離に変換
  float dstM = (float)intervalUS * 340.0 / 1000.0 / 1000.0;  // センサー出力の値（単位：m）  音速：340m/s(15℃)
  float dstCMs = dstM * 100.0;  // センサー出力の値（単位：cm）
 
    return String(dstCMs);                // 距離を出力（単位：cm）
 

}




void setup(){
  // シリアルを指定
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);           // SSIDとパスの設定
  delay(100);                        // 追記：このdelayを入れないと失敗する場合がある
  WiFi.softAPConfig(ip, ip, subnet); // IPアドレス、ゲートウェイ、サブネットマスクの設定
  
  IPAddress myIP = WiFi.softAPIP();  // WiFi.softAPIP()でWiFi起動
  
  //シリアルにIPアドレスを表示
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server start!");

  
 
  // SPIFFSがうまく起動できているか確認
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }



 

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/home.html");
  });
  server.on("/xg.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/xg.html");
  });
  server.on("/vg.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/vg.html");
  });
  server.on("/ag.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ag.html");
  });
  server.on("/x.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/x.html");
  });
  server.on("/v.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/v.html");
  });
  server.on("/xv.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/xv.html");
  });
  server.on("/a.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/a.html");
  });
  server.on("/ac.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ac.html");
  });
  server.on("/vc.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/vc.html");
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readHCSR04cm().c_str());
  });







  // Start server
  server.begin();
}
 
void loop(){
  
}
