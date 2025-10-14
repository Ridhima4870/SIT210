Pet Tracker System

## Overview
The **Pet Tracker System** is an embedded IoT project designed to monitor a pet’s movement, location, and environmental conditions in real time.  
The system combines microcontroller and single-board computer technologies (Arduino Nano 33 IoT and Raspberry Pi 4) to collect data from sensors and transmit it to a cloud platform for analysis and visualization.

This repository presents the system design, planned architecture, and development workflow for the prototype, which is currently under construction.

---

## Objectives
- To develop an IoT-based tracking system that records a pet’s **location (GPS)** and **activity (gyroscope)**.  
- To sense **temperature and humidity** in the pet’s environment using a DHT22 sensor.  
- To use **Raspberry Pi** for data processing, MQTT communication, and database storage.  
- To visualize collected data through a **Plotly Dash dashboard** showing location, movement, and environmental trends.  

---

## Planned Hardware Components
- **Arduino Nano 33 IoT** – for sensor data collection.  
- **Raspberry Pi 4** – acts as a local hub and MQTT subscriber, forwarding data to the cloud.  
- **GPS Module (NEO-6M)** – provides live geographic coordinates of the pet.  
- **LSM6DS3 Gyroscope/Accelerometer** – tracks pet movement and activity level.  
- **DHT22 Sensor** – measures temperature and humidity.  
- **Power Supply (Battery pack / Power bank)** – for mobile operation.  
- **Optional Buzzer or LED** – to indicate system status.  

---

## Planned Software Tools
- **Arduino IDE** – for programming the microcontroller.  
- **Python 3** on **Raspberry Pi** – for MQTT subscription, GPS parsing, and database handling.  
- **HiveMQ Cloud** – MQTT broker for data publishing and subscription.  
- **Firebase / MongoDB** – NoSQL databases for long-term data storage.  
- **Plotly Dash** – web dashboard for live visualization.  
- **Geopy / Folium** – Python libraries for plotting GPS coordinates on a map.  

---

## System Architecture (Planned)

### 1. Data Acquisition Layer  
Arduino Nano 33 IoT collects data from the DHT22 and LSM6DS3 sensors and sends readings to the Raspberry Pi using serial communication.

### 2. Communication Layer  
Raspberry Pi publishes the received data (including GPS coordinates) to an MQTT topic on HiveMQ Cloud.  
A Python subscriber script listens to the same topic and stores data in Firebase or MongoDB.

### 3. Data Processing & Visualization Layer  
A Plotly Dash app retrieves stored data and displays:  
- Pet’s live location on a map  
- Movement/activity trends  
- Temperature and humidity graphs  

**Planned Data Flow:**  
Sensors → Arduino Nano 33 IoT → Serial → Raspberry Pi 4 → MQTT (HiveMQ) → Cloud DB → Plotly Dash Dashboard

---

## Project Status
- ✅ Project planning and hardware architecture finalised.  
- 🔄 Prototype assembly and GPS integration in progress.  
- 🧪 Testing, data visualization, and optimization scheduled for the next phase.  

---

## Future Work
- Implement a **mobile notification system** for location or temperature alerts.  
- Add **battery management** and low-power operation.  
- Test GPS accuracy outdoors and compare with cloud-logged data.  
- Deploy the Plotly Dash dashboard on Raspberry Pi for standalone use.  

---

## Author
**Ridhima Sharma**  
Senior Cardiologist | Embedded Systems Student  
Auckland, New Zealand  

*(This repository was created as part of the Embedded Systems unit portfolio project.)*

---

## Note
The physical prototype is currently under development.  
Source code, Arduino sketches, and Raspberry Pi scripts will be uploaded after implementation and testing are complete.
