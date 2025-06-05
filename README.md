
# **Gas Leakage Monitoring System with ESP32**

## **Description**

This project aims to develop a gas leakage monitoring system using the **ESP32** and a **MQ-2 gas sensor**. The system monitors the sensor's reading and activates **status LEDs** (green, blue, red) according to the gas levels. Additionally, the project sends **Telegram notifications** when the level reaches moderate or critical values.

## **Objective**

The objective of this project is to demonstrate the creation of a simple IoT system for gas leakage monitoring. Using the **ESP32** as the microcontroller, the system can:
- Monitor the **MQ-2 sensor's** value simulating gas concentration.
- Activate LEDs to indicate leakage status: **green** (normal), **blue** (attention), and **red** (critical).
- Send **Telegram notifications** to the user’s phone when a critical level is detected.

## **Components Used**

- **ESP32** (microcontroller)
- **MQ-2 Gas Sensor** (detects gases like GLP, butane, alcohol, smoke, etc.)
- **3 LEDs** (green, blue, red)
- **220Ω Resistors** (to limit current to the LEDs)
- **Jumper wires**
- **Breadboard** (for assembly)

## **Technologies Used**

- **Arduino IDE** for programming the **ESP32**
- **Wi-Fi** for network connection and message sending
- **Telegram Bot API** for sending alert notifications
- **Blynk (optional)** for real-time data visualization on the mobile app

## **How It Works**

1. **ESP32 connects to Wi-Fi**: The ESP32 connects to the Wi-Fi network defined in the code.
2. **MQ-2 Sensor reading**: The MQ-2 gas sensor value is read from GPIO 34 and mapped between 0 and 4095.
3. **Status LEDs**:
   - **Green LED**: Lit when the sensor value is below the **1000** threshold.
   - **Blue LED**: Lit when the value is between **1000 and 2500**, indicating a **moderate level**.
   - **Red LED**: Lit when the value exceeds **2500**, indicating a **critical level**.
4. **Telegram notification**:
   - **1-minute interval** for **moderate level** (blue LED on).
   - **10-second interval** for **critical level** (red LED on).

## **Setup**

### **Wi-Fi**
In the code, configure your **SSID** and **password** for the Wi-Fi network:
```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

### **Telegram**
1. Create a **Telegram bot** using **BotFather**.
2. Get the **Token** for the bot and replace it in the code:
```cpp
String botToken = "YOUR_BOT_TOKEN";
String chatID = "YOUR_CHAT_ID";
```
3. Send a message to your **chat ID** to test functionality.

### **Blynk (optional)**
1. **Create a Blynk Account**
   - Download the **Blynk app** (available for iOS and Android).
   - Sign up for a free account.

2. **Create a New Project**
   - Open the app, tap on **"New Project"**.
   - Select the **ESP32** as the device.
   - Choose **Wi-Fi** as the connection type.
   - The app will generate an **Auth Token** for your project. Copy and paste this token into the **BLYNK_AUTH_TOKEN** in your code.

3. **Add Widgets in the Blynk App**
   - Open your Blynk project.
   - Add a **Gauge** or **Value Display** widget to monitor the **MQ-2 sensor’s** value in real-time.
   - Link the widget to **Virtual Pin V1** (or another pin you assign).

4. **Configure the Code**
   - In your Arduino IDE code, make sure you are using the correct Auth Token and Wi-Fi credentials.

## **How to Use**

1. **Upload the code to the ESP32** using Arduino IDE.
2. **Open the Serial Monitor** to see the **MQ-2 sensor** readings in real-time.
3. **Watch the LEDs**: the system will change from green to blue or red based on the sensor value.
4. **Receive notifications on Telegram** when a critical or moderate level is detected.

## **Conclusion**

This project is a **basic demonstration** of how an IoT system can be used to **monitor hazardous conditions**, such as a gas leak. It can be expanded to include **more sensors**, **additional notifications**, **remote control**, and **improved interfaces**.

## **License**

This project is open-source and can be used and modified under the terms of the license.
