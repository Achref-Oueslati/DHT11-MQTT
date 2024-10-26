#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
#define wifi_ssid "Redmi Note 10 Pro"
#define wifi_password "12345676"

// MQTT Broker details
#define mqtt_server  "192.168.88.140"
#define Humidity_topic  "esp32/dht11/humidity"
#define temperature_topic "esp32/DHT11/temperature"
#define relay_topic "esp32/relay/status"


// Pins
#define DHTPIN 4         // Pin where the DHT11 is connected
#define DHTTYPE DHT11    // DHT11 sensor
#define RELAY_PIN 26      // Pin where the relay is connected

// DHT Sensor setup
DHT dht(DHTPIN, DHTTYPE);

bool relayState = false;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 seconds on/off cycle

// WiFi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

  if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}



void setup() {
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);


  // Setup WiFi and MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read from sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Ensure valid readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(temperature);
   Serial.print(" *C ");


  // Publish sensor data to MQTT broker
      Serial.print("Temperature in Celsius:");
      Serial.println(String(temperature).c_str());
      client.publish(temperature_topic, String(temperature).c_str(), true);

      Serial.print("Humidity:");
      Serial.println(String(humidity).c_str());
      client.publish(Humidity_topic, String(humidity).c_str(), true);

  // Relay control with MQTT publish

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
   previousMillis = currentMillis;
    
    // Toggle relay state
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
    
    // Publish relay state
    String relayStatus = relayState ? "ON" : "OFF";
    Serial.print("Relay status: ");
    Serial.println(relayStatus);
    client.publish(relay_topic, relayStatus.c_str(), true);
  }


  // Delay before next reading
  delay(5000); // Publish every 5 seconds
}