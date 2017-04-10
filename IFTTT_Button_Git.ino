#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// connect button to GPIO pin D2
int BUTTON_PIN = D2;

const char* ssid = "SSID HERE";
const char* password = "PASSWORD HERE";

//make sure to use http here (non SSL)
const char* webhookURL = "http://maker.ifttt.com/trigger/{event}/with/key/INSERT_KEY_HERE";

bool isWaitingForButtonPress = true;
bool madeHTTPRequest = false;

HTTPClient http;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected to: " + String(ssid));
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  
  pinMode(BUTTON_PIN,INPUT);
}

void loop() {
  int status = digitalRead(BUTTON_PIN);

  if(status == HIGH && madeHTTPRequest != true) {
    http.begin(webhookURL);
    http.POST("");
    Serial.println(http.writeToStream(&Serial));
    http.end();
    Serial.println("Pressed...");
      
    madeHTTPRequest = true;    
    isWaitingForButtonPress = true;
  
  } else {
    if (isWaitingForButtonPress == true){
      
      Serial.println("Waiting...");
      isWaitingForButtonPress = false;
      madeHTTPRequest = false;
    
    }
  }
}
 


