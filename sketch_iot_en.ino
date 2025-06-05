#include <WiFi.h>
#include <HTTPClient.h>


// Wi-Fi settings
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram settings
String botToken = "YOUR_BOT_TOKEN";
String chatID = "YOUR_CHAT_ID";

// Blynk settings
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
#include <BlynkSimpleEsp32.h>


#define SENSOR_PIN 34
#define GREEN_LED_PIN 23
#define BLUE_LED_PIN 21
#define RED_LED_PIN 5

int blue_threshold = 1000;
int red_threshold = 2500;

unsigned long last_msg_blue = 0;
unsigned long last_msg_red = 0;


void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Wi-Fi connection via Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Connect Wi-Fi for Telegram (if Blynk.begin doesn't connect Wi-Fi, ensure connection here)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Wi-Fi connected!");
}


void sendTelegram(String message) {
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + message;

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.println("Message sent to Telegram!");
  } else {
    Serial.print("Sending error:");
    Serial.println(httpResponseCode);
  }

  http.end();
}


void loop() {
  Blynk.run();

  int measure = analogRead(SENSOR_PIN);
  Serial.print("Measure:");
  Serial.println(measure);

  unsigned long current = millis();

  // Send data to Blynk transforming it into percentage
  Blynk.virtualWrite(V0, map(measure, 0, 4095, 0, 100));

  if (measure < blue_threshold) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

  } else if (measure < red_threshold) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);

    // Sends a message via Telegram every 15 seconds in the alert zone
    if (WiFi.status() == WL_CONNECTED and (current - last_msg_blue >= 15000)) {
      int percentage = map(measure, 0, 4095, 0, 100);
      String message = "⚠️ ATTENTION: Moderate level detected! Measure:" + String(percentage) + "%";
      sendTelegram(message);
      last_msg_blue = current;
    }

  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);

    // Sends a message via Telegram every 5 seconds in the critical zone
    if (WiFi.status() == WL_CONNECTED and (current - last_msg_red >= 5000)) {
      int percentage = map(measure, 0, 4095, 0, 100);
      String message = "🚨 ALERT! Critical level detected! Measure: " + String(percentage) + "%";
      sendTelegram(message);
      last_msg_red = current;
    }
  }

  delay(1000); // Delay to stabilize the reading every 1 second
}
