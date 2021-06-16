# Connection_Settings
BT_PORT_NAME = '/dev/cu.usbmodem141401'
# BT_PORT_NAME = '/dev/ttyACM0'

# ENCODING DATA
ENCODER_DC = {
    'B': 'encoder_year',
    'A': 'encoder_month',
    'C': 'encoder_day',
    'D': 'encoder_button',
    'E': 'serial_sent'
}

DATA_DC = {
    'encoder_year': 0,
    'encoder_month': 0,
    'encoder_day': 0,
    'encoder_button': 0,
    'serial_sent': 0
}

# Sending message
TURN_OFF_LED_1 = b"A1\nB0\nC0\n"
TURN_OFF_LED_2 = b"A0\nB1\nC0\n"
TURN_OFF_LED_3 = b"A0\nB0\nC1\n"

