String ssid     = "IoT Temperature";  // Nama SSID
String password = ""; //password
String host     = "api.thingspeak.com"; //Untuk membuka API
const int httpPort   = 80;
String uri     = "/update?api_key=8WF3U9329MLSLA86=";

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
   	Serial.begin(9600);//kecepatan pengiriman dan penerimaan data
  	lcd.begin(0, 2);
    lcd.print("Hello, Have a");
  	lcd.setCursor(4, 1);
    lcd.print(" Nice Day!!");
    delay(4000);
    lcd.clear();
  
  	setupESP8266();//setup wifi modulenya       
}

int setupESP8266(void) {
  // Memulai Wifi Module untuk Serial nya
  Serial.begin(115200);   
  Serial.println("AT");   // Koneksi pada pada Tx / Rx ke ESP8266
  delay(10);        
  if (!Serial.find("OK")) return 1;
    
  //Mengkonek Sirkuit 123D ke SSID
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);       
  if (!Serial.find("OK")) return 2;
  
  // Membuka koneksi TCP ke Host
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void loop() {
  data();
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.clear();
}


void data(void) {
  
  int temp = map(analogRead(A0),20,358,-40,124);
  
  //Tampilin Temp di Lcd
    lcd.print("Temp Now: ");
    lcd.setCursor(5, 1);
    lcd.print(temp);
  	lcd.print(" Celcius");
    delay(500);
  
  //Membangun HTTP
  String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  //Mengirim panjang message
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); 

  // Mengirim http request
  Serial.print(httpPacket);
  delay(10); 
  if (!Serial.find("SEND OK\r\n")) return;
   
}





  
 
  
  
  
    
