import serial
import logging
from langchain_openai import ChatOpenAI

# Configure logging
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(levelname)s - %(message)s',
)
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

# Initialize ChatGPT API
llm = ChatOpenAI(
    model="gpt-3.5-turbo",
    base_url="https://api.avalai.ir/v1",
    api_key="aa-6QKE8fBnHv94Qd2avzF2KarvnvJfKcOFEKLzNJ5tOcp5hNSh"
)

SERIAL_PORT = '/dev/cu.usbserial-110'  # Update with your serial port
BAUD_RATE = 115200


def listen_to_arduino():
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            logger.info("Listening for commands from Arduino...")
            while True:
                if ser.in_waiting > 0:  # Check if data is available
                    prompt = ser.readline().decode().strip()
                    logger.info(f"Received prompt from Arduino: {prompt}")

                    # Process the prompt using ChatGPT API
                    action = process_prompt(prompt)

                    # Send the action back to Arduino
                    logger.info(f"Sending action to Arduino: {action}")
                    ser.write((action + '\n').encode())  # Send response
    except serial.SerialException as e:
        logger.error(f"Serial communication error: {e}")


def process_prompt(prompt):
    logger.info(f"Processing Arduino prompt: {prompt}")

    if not prompt:
        logger.warning("Invalid input. Empty prompt received.")
        return "X"  # Invalid action placeholder

    message = [
        {
            "role": "system",
            "content": """
            You are an intelligent assistant managing an IoT system that controls LED lights. 
            Your task is to understand user prompts and determine the appropriate action to control the lights. 
            Here are the available functions and their respective commands:

            A: Turn on Room LED
            B: Turn off Room LED
            C: Turn on Kitchen LED
            D: Turn off Kitchen LED

            **Instructions**:
            1. You must analyze the user's message and identify the action required.
            2. Only respond with a **single uppercase letter** (A, B, C, or D).
            3. Do not include any additional text, explanations, or symbols.
            4. Assume that the user messages are written in either **English** or **Persian**.
            5. Always follow the rules provided and prioritize clarity and accuracy.

            **Example User Prompts**:
            - "Please turn off the kitchen light." → Respond: D
            - "اتاق خیلی روشنه، خاموشش کن." → Respond: B
            - "Turn on kitchen light." → Respond: C
            """
        },
        {"role": "user", "content": prompt}
    ]

    try:
        logger.info("Sending prompt to ChatGPT API...")
        result = llm.invoke(message)
        action = result.content.strip().upper()  # Ensure the action is uppercase
        logger.info(f"ChatGPT response (action): {action}")

        # Validate the action
        if action not in ['A', 'B', 'C', 'D']:
            logger.error(f"Invalid action received from ChatGPT: {action}")
            return "X"  # Invalid action placeholder

        return action  # Return valid action
    except Exception as e:
        logger.error(f"An error occurred: {e}")
        return "X"  # Error placeholder


if __name__ == "__main__":
    listen_to_arduino()
