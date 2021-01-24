/*
      By Vasily Davydov (vas-dav)
      2021      
      {Crypto Ticker}
      Program written for NodeMCU v1.0 with ESP8266

*/


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>


//test host: sandbox-api.coinmarketcap.com
//test API: b54bcf4d-1bca-4e8e-9a24-22ff2c3d462c
//main host: pro-api.coinmarketcap.com

bool state = 1;
const long UPD = 5 * 60 * 1000;
const char ssid[] = "Your WiFi";  
const char password[] = "password";
String line = "";

LiquidCrystal lcd(D6, D5, D1, D2, D3, D4); 


//Web address to read from 
const char host[] = "sandbox-api.coinmarketcap.com";
//const PORT
const int httpsPort = 443;  
const char API [] = "b54bcf4d-1bca-4e8e-9a24-22ff2c3d462c"; // Your own API key (test key is working only with test host)
const char trustRoot[] = R"EOF(-----BEGIN CERTIFICATE-----
MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ
RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD
VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX
DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y
ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy
VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr
mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr
IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK
mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu
XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy
dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye
jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1
BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3
DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92
9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx
jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0
Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz
ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS
R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp
-----END CERTIFICATE-----
)EOF";
X509List cert(trustRoot);
/*=======================================================================
                              Ticker ON
         - Start Screen
         - Establishing WiFi Connection                        
  =======================================================================*/

void setup() {
  
  int load=0;
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("BitCoin Ticker");
  lcd.setCursor(3,1);
  lcd.print("Power ON");
  delay(2000);
  lcd.clear();
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        // This hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  
  // Wait for connection
  lcd.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    for (int i = 0; i < 15; i++)
    {
    lcd.setCursor(i,1);
    lcd.print(".");
    delay(500);
    }
  }

  
  Serial.println("");
  lcd.clear();
  lcd.print("Connected WiFi"); //If connection successful display on LCD
  delay(1000);
  Serial.println(ssid);
}

/*=======================================================================
                          Ticker Loop 
        - Connection to a Crypto Server
        - Gathering DATA from it
        - Forming a Json Doc and extracting DATA
        - Showing DATA on the LCD screen                 
  =======================================================================*/
void loop() {
  
    lcd.clear();
    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    
    Serial.print("Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
      delay(500);
      lcd.setCursor(0,0);
      lcd.print("Requesting");
      lcd.setCursor(0,1);
      lcd.print("DATA");
      for (int d = 4; d < 12; d++)
      {
        lcd.setCursor(d,1);
        lcd.print(".");
        delay(500);
        Serial.print(".");
      }
      now = time(nullptr);
    }
    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
  
    WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
  
    Serial.println(host);
  
    httpsClient.setTrustAnchors(&cert);
    httpsClient.setTimeout(5000); // 5 Seconds
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("Updating Data");
    int r=0; //retry counter
    while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
        delay(100);
        lcd.setCursor(0,1);
        lcd.print(".");
        r++;
    }
    if(r==30) {
      lcd.setCursor(0,0);
      lcd.print("Update failed");
    }
    else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Data Updated");
      delay(2000);
    }
    
    String ADCData, getData, Link;
    int adcvalue=analogRead(A0);  //Read Analog value of LDR
    ADCData = String(adcvalue);   //String to interger conversion
  
    //GET Data
    Link = "/v1/cryptocurrency/quotes/latest?symbol=BTC,ETH";
  
    Serial.print("requesting URL: ");
    Serial.println(host+Link);
  
    httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "X-CMC_PRO_API_KEY: " + API + "\r\n" +             
                 "Connection: close\r\n\r\n");
  
    Serial.println("request sent");
                    
    while (httpsClient.connected()) {
        
        line = httpsClient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
  
    Serial.println("reply was:");
    Serial.println("---------");
    String line = "";
    Serial.println(line);
    bool responseReceived = false;
    while(httpsClient.available() ){   
    if (!responseReceived) {
    responseReceived = true;
    httpsClient.readStringUntil('\n');
  } else {
    line += httpsClient.readStringUntil('\n');
    }
    }
    Serial.println(line); //Print response
    Serial.println("---------");




  DynamicJsonDocument cDATA (4096);


  deserializeJson(cDATA, line);
  float BTC = cDATA["data"]["BTC"]["quote"]["USD"]["price"].as<float>();
  float percBIT = cDATA["data"]["BTC"]["quote"]["USD"]["percent_change_24h"].as<float>();
  float ETH = cDATA["data"]["ETH"]["quote"]["USD"]["price"].as<float>();
  float percETH = cDATA["data"]["ETH"]["quote"]["USD"]["percent_change_24h"].as<float>();
  lcd.clear();
  delay(500);


  /* Entering a loop that has a delay of 34 * 9000 ms, 
     because the API has limitational connection per day */

  for (int s  = 1; s < 34; s++)
  {
    delay(9000);
    state = !state;
    Serial.println(s*9000);
    if (state)
  {
    
    lcd.setCursor(0,0);
    lcd.print("Ethereum");
    lcd.setCursor(12,0);
    lcd.print("24h%");
    lcd.setCursor(11,1);
    lcd.print(percETH);
    lcd.setCursor(0,1);
    lcd.print(ETH);

  } else
  {
    lcd.setCursor(0,0);
    lcd.print("Bitcoin ");
    lcd.setCursor(12,0);
    lcd.print("24h%");
    lcd.setCursor(11,1);
    lcd.print(percBIT);
    lcd.setCursor(0,1);
    lcd.print(BTC);
  }
    
  }
  
  
// Loop ends and a new connection begins
  
  Serial.println("closing an old connection and making a new one");

}
//=======================================================================
