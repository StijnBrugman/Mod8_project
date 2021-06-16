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
    'I': 'distance_E',
    'Z': 'serial_sent'
}



DATA_DC = {
    'encoder_year':     0,
    'encoder_month':    0,
    'encoder_day':      0,
    'encoder_button':   0,
    'distance_A':       None,
    'distance_B':       None,
    'distance_C':       None,
    'distance_D':       None,
    'distance_E':       None
}

LIST_CITIES = ["Rotterdam", "Driel boven", "IJmuiden Noordersluis", "Maastricht", "Utrecht"]

CONVERT_TO_CITY_DC = {
    'distance_A': LIST_CITIES[0],
    'distance_B': LIST_CITIES[1],
    'distance_C': LIST_CITIES[2],
    'distance_D': LIST_CITIES[3],
    'distance_E': LIST_CITIES[4]
}

MESSAGES_DC = {
    LIST_CITIES[0]: [
        b"A1\nB0\n",
        b"A0\nB1\n",
        b"A0\nB0\n"
    ],
    LIST_CITIES[1] : [
        b"C1\nD0\n",
        b"C0\nD1\n",
        b"C0\nD0\n"
    ],
    LIST_CITIES[2]: [
        b"E1\nF0\n",
        b"E0\nF1\n",
        b"E0\nF0\n"
    ],
    LIST_CITIES[3]: [
        b"G1\nH0\n",
        b"G0\nH1\n",
        b"G0\nH0\n"
    ],
    LIST_CITIES[4]: [
        b"I1\nJ0\n",
        b"I0\nJ1\n",
        b"I0\nJ0\n"
    ]
}

MAX_DISTANCE = 30
MIN_DISTANCE = 2

MAX_HEIGHT = 4000
MIN_HEIGHT = -100

# Sending message
TURN_OFF_LED_1 = b"A1\nB0\nC0\n"
TURN_OFF_LED_2 = b"A0\nB1\nC0\n"
TURN_OFF_LED_3 = b"A0\nB0\nC1\n"
WATERVALVE_A_1 = b"A0\nB0\nC1\n"

