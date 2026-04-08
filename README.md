🏠 IoT-Based Theft Control & Auto Alerting System
📌 Overview

The IoT-Based Theft Control System is an intelligent security solution designed to detect unauthorized access using multiple sensors and provide real-time alerts to users. The system integrates IoT, embedded systems, and communication technologies to enhance security in homes, offices, and restricted areas.

It continuously monitors the environment using sensors and immediately triggers alerts through SMS and IoT platforms when suspicious activity is detected.

🎯 Features
🔍 Real-time intrusion detection using sensors
🚨 Automatic buzzer alert on unauthorized access
📩 Instant SMS notifications to users
🌐 Remote monitoring via IoT platform
🗂️ Data logging for security analysis
🔐 RFID-based access control
⚡ Works even during internet failure (GSM support)
🔌 Hardware integration with Arduino


🛠️ Tech Stack
💻 Software
Embedded C (Arduino Programming)
Arduino IDE
Mobile Telnet Application
IoT Cloud Platform
🤖 Hardware / IoT
Arduino Uno
RFID Module
Tilt Sensor
Wi-Fi Module
GSM Module
LCD Display (16x2)
Buzzer
Motor Driver (L293D)

📁 Project Structure
project/
│── code/
│   ├── main.ino              # Main Arduino code
│   ├── wifi_setup.ino        # Wi-Fi initialization
│   ├── rfid_module.ino       # RFID handling
│   ├── sensor_module.ino     # Sensor integration
│
│── hardware/
│   ├── circuit_diagram.png
│   ├── components_list.txt
│
│── docs/
│   ├── report.pdf
│
│── logs/
│   ├── access_logs.txt

⚙️ Installation & Setup
1️⃣ Install Arduino IDE
Download and install Arduino IDE
2️⃣ Connect Hardware
Connect Arduino with:
RFID module
Tilt sensor
Buzzer
LCD display
Wi-Fi module
3️⃣ Upload Code
Open Arduino IDE
Select Board → Arduino Uno
Upload the code

🔐 System Setup
Configure Wi-Fi module
Set valid RFID card ID in code
Connect system to Mobile Telnet

📸 Working Process
User scans RFID card
System verifies authentication
If valid → Motor starts & access granted
If invalid → Buzzer alert triggered
Tilt sensor detects abnormal activity
Alert sent via Telnet/SMS
System logs event

▶️ Run System
Power ON Arduino
Connect via Mobile Telnet
Monitor system activity in real-time

🌐 User Interface
Mobile Telnet acts as UI
Displays:
Access status
Intrusion alerts
Sensor data

🗄️ Data Storage
Stores:
Access attempts
Intrusion alerts
Sensor readings

📩 Alert System
Unauthorized access → Buzzer ON
SMS / Telnet alert sent
Immediate user notification

🔌 Hardware Support
Arduino-based system
Supports integration with:
Smart locks
Alarm systems
IoT dashboards

🚀 Future Enhancements
Mobile app development
AI-based intrusion detection
Face recognition integration
Cloud database storage
Multi-location monitoring

📊 Use Cases
Smart Homes
Office Security
Vehicle Theft Detection
Industrial Monitoring

⚠️ Limitations
Depends on sensor accuracy
Limited range of hardware
Requires proper setup
Basic UI (Telnet-based)

👩‍💻 Author

Kasarla Lakshmi Prasanna
B.Tech CSE(final year)

📜 License

This project is for academic purposes only.

🙌 Acknowledgements
Arduino Community
IoT Developers
Embedded Systems Research
