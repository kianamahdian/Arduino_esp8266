Here’s a structured GitHub README for your project based on the provided report:  

---

# 🏠 IoT Smart Home Assistant using ESP8266

A project for remotely controlling home appliances via Wi-Fi using the ESP8266 module and AI-powered voice/text processing.

## 📌 Project Overview

This project is an **IoT-based smart home assistant** designed to control household devices remotely. The **ESP8266** module serves as a **Wi-Fi-connected web server**, allowing users to send commands via a simple web interface. Additionally, it integrates **natural language processing (NLP)** to interpret commands and send appropriate responses.

### 🔹 Features
- **Web-based control:** Users can turn lights on/off via a browser.
- **AI-powered assistant:** Uses **ChatGPT** to interpret natural language commands.
- **ESP8266 Web Server:** Handles HTTP requests and executes control actions.
- **Serial Communication:** Interacts with a Python script to process user commands.
- **Real-time device control:** Supports turning LEDs on/off via text commands.

---

## 🛠️ Technologies Used
### Hardware:
- **ESP8266** Wi-Fi Module
- LED lights (for demonstration)

### Software:
- **Arduino IDE** (for programming the ESP8266)
- **Python** (for processing commands)
- **LangChain + OpenAI API** (for NLP-based command interpretation)
- **HTML, JavaScript** (for web interface)

---

## ⚙️ System Architecture

1. **ESP8266 Web Server:**  
   - Connects to a Wi-Fi network.
   - Hosts a webpage for user input.
   - Forwards user commands to the Python script via serial communication.

2. **Python Script (AI Processing):**  
   - Reads commands from ESP8266.
   - Sends them to **ChatGPT** via API.
   - Parses the AI response and sends appropriate signals back to ESP8266.

3. **Command Execution:**  
   - ESP8266 executes corresponding actions (turning LEDs on/off).

---

## 🚀 Setup & Installation

### 1️⃣ ESP8266 Setup
- Install **Arduino IDE** and ESP8266 board libraries.
- Connect ESP8266 to your computer.
- Upload the provided **Arduino code**.

### 2️⃣ Python Setup
- Install dependencies:
  ```bash
  pip install pyserial langchain_openai
  ```
- Modify **serial port** settings in `main.py` to match your device.
- Run the Python script:
  ```bash
  python main.py
  ```

### 3️⃣ Web Interface
- Connect to the ESP8266's **Wi-Fi network**.
- Open the assigned **IP address** in a web browser.
- Enter a command (e.g., "Turn on kitchen light").
- The system processes and executes the request.

---

## 📜 Code Structure

```
├── esp8266_code.ino   # ESP8266 Web Server Code (Arduino)
├── main.py            # Python script for AI processing
├── README.md          # Documentation
└── requirements.txt   # Python dependencies
```

---

## 🔬 Example Commands
| Command | AI Response | Action |
|---------|------------|--------|
| "Turn on the kitchen light" | `C` | Turns on kitchen LED |
| "Please switch off the room light" | `B` | Turns off room LED |
| "Turn on room light" | `A` | Turns on room LED |
| "Turn off kitchen light" | `D` | Turns off kitchen LED |

---

## 📌 Future Improvements
- Voice command support.
- Mobile app integration.
- More device compatibility.

---

## 📌 Contributors
- **Kianna Mehdian**  
- **Yasamin Akbari**  

Developed for the **Internet of Things (IoT) Programming** course at the **University of Isfahan**.

---

