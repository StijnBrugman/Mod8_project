# Connection_Settings
BT_PORT_NAME = '/dev/cu.usbmodem142401'
# BT_PORT_NAME = '/dev/ttyACM0'

# ENCODING DATA
ENCODER_DC = {
    'B': 'encoder_year',
    'A': 'encoder_month',
    'C': 'encoder_day',
    'D': 'encoder_button',
    'E': 'distance_A',
    'F': 'distance_B',
    'G': 'distance_C',
    'H': 'distance_D',
    'I': 'distance_A',
    'Z': 'serial_sent'
}

DATA_DC = {
    'encoder_year':     0,
    'encoder_month':    0,
    'encoder_day':      0,
    'encoder_button':   0,
    'distance_A':       0,
    'distance_B':       0,
    'distance_C':       0,
    'distance_D':       0,
    'distance_E':       0
}

# Sending message
TURN_OFF_LED_1 = b"A1\nB0\nC0\n"
TURN_OFF_LED_2 = b"A0\nB1\nC0\n"
TURN_OFF_LED_3 = b"A0\nB0\nC1\n"
WATERVALVE_A_1 = b"A0\nB0\nC1\n"

LIST_CITIES = ["IJmuiden Noordersluis", "Driel boven", "Maastricht", "Rotterdam"]