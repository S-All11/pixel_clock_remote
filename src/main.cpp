#include <M5Stack.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-FiのSSIDとパスワードを入力してください
const char* ssid = "PI-AP";
const char* password = "6v5wh465333px";

// HTTPサーバーのポート番号を指定
WebServer server(80);//

String timeCode = "9999";  // 初期値として "9999" を設定
String seting_time ="9999" ;


void handleRoot() {
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("Get Client request now!!");
  seting_time = timeCode;
  // クライアントに現在のseting_timeを返す
  server.send(200, "text/plain", seting_time);
  if(seting_time!="9999"){
    timeCode = 9998;
  }
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  
  // WiFi接続の開始
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  M5.Lcd.println("\nConnected to WiFi!");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());
  
  // ルートURLにアクセスがあった場合のハンドラーを設定
  server.on("/", handleRoot);
  
  // サーバーを開始
  server.begin();
}

void loop() {
  server.handleClient();  // クライアントからの要求を処理
  
  M5.update();  // M5Stackのボタンの状態を更新
  
  // ボタンA, B, Cの操作でtimeCodeを設定
  if (M5.BtnA.isPressed()) {
    timeCode = "1111";  // 例えば、ボタンAを押すと1234に設定
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.println("Time Code set to 1111");
    
  }
  if (M5.BtnB.isPressed()) {
    timeCode = "1234";  // 例えば、ボタンBを押すと1111に設定
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.println("Time Code set to 1234");
  }
  if (M5.BtnC.isPressed()) {
    timeCode = "9999";  // 例えば、ボタンCを押すと9999に設定
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.println("Time Code set to 9999");
  }
}

// void time_command(){
//   seting_time = 9998;
//   //server.send(200, "text/plain", "Current Time Code: " + seting_time);
//   server.send(200, seting_time);
//   }

// void A_btn(){//Aボタンが押された際の処理
//  timeCode++;
// }

// void B_btn(){//Bボタンが押された際の処理
//  timeCode--;
// }

// void C_btn(){//Cボタンが押された際の処理
//  
// }