# DHT11-MQTT

# ESP32 IoT Project with MQTT, DHT11 Sensor, and Relay Control

This project enables an ESP32 to connect to WiFi, read temperature and humidity data from a DHT11 sensor, control a relay, and communicate with an MQTT broker. It publishes sensor data and relay status to MQTT topics, allowing for remote monitoring and control.

## Features

- **WiFi Connectivity**: Connects the ESP32 to a specified WiFi network.
- **MQTT Communication**: Publishes temperature, humidity, and relay status data, and reconnects if the connection drops.
- **DHT11 Sensor Integration**: Reads temperature and humidity data from the DHT11 sensor.
- **Relay Control**: Toggles relay state every 2 seconds, with real-time status updates via MQTT.

## Hardware Required

1. ESP32 Microcontroller
2. DHT11 Temperature and Humidity Sensor
3. Relay Module
4. MQTT Broker (Mosquitto)

## Software Requirements

- PlatformIO or Arduino IDE
- PubSubClient (for MQTT)
- DHT Library

## Setup and Usage

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/ESP32-IoT-Project.git
   ```
2. **Configure WiFi and MQTT**
   - Update the WiFi credentials (`wifi_ssid`, `wifi_password`) in the code.
   - Set the Mosquitto IP address and topics in the code.

3. **Upload Code to ESP32**
   - Connect the ESP32 to your computer.
   - Compile and upload the code using PlatformIO or Arduino IDE.

4. **Monitor Serial Output**
   - Open the Serial Monitor to view real-time temperature, humidity, and relay status.

5. **Subscribe to MQTT Topics**
   - Use an MQTT client to subscribe to the following topics:
     - `esp32/dht11/humidity`
     - `esp32/dht11/temperature`
     - `esp32/relay/status`

## Example Output

```plaintext
Connecting to WiFi...
WiFi connected, IP: 192.168.88.XX
Temperature: 23.4 °C
Humidity: 54.2 %
Relay status: ON
```

## Code Breakdown

```cpp
// WiFi and MQTT Configuration
#define wifi_ssid "your_ssid"
#define wifi_password "your_password"
#define mqtt_server "broker_ip"
#define Humidity_topic "esp32/dht11/humidity"
#define temperature_topic "esp32/DHT11/temperature"
#define relay_topic "esp32/relay/status"
```

- **WiFi Configuration**: Sets the WiFi SSID and password.
- **MQTT Broker and Topics**: Defines the Mosquitto IP and MQTT topics.

```cpp
// Initialize DHT Sensor and Relay Pin
#define DHTPIN 4
#define RELAY_PIN 26
DHT dht(DHTPIN, DHTTYPE);
```

- **DHT11 Sensor**: Reads temperature and humidity data.
- **Relay Module**: Toggles its state every 2 seconds, publishing the relay status via MQTT.

## Contact

Feel free to reach out if you have any questions or suggestions!
