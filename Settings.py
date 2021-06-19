# Connection_Settings
BT_PORT_NAME = '/dev/cu.usbmodem142401'
# BT_PORT_NAME = '/dev/ttyACM0'

# ENCODING DATA
ENCODER_DC = {
    'A': 'encoder_year',
    'B': 'encoder_month',
    'C': 'encoder_day',
    'D': 'encoder_button',
    'E': 'distance_A',
    'F': 'distance_B',
    'G': 'distance_C',
    'H': 'distance_D',
    'I': 'distance_E',
    'J': 'flow_In',
    'K': 'flow_Out',
    'L': 'Water_Sensor',
    'Z': 'serial_sent'
}

DATA_DC = {
    'encoder_year': 0,
    'encoder_month': 0,
    'encoder_day': 0,
    'encoder_button': 0,
    'distance_A': None,
    'distance_B': None,
    'distance_C': None,
    'distance_D': None,
    'distance_E': None,
    'flow_In': 0,
    'flow_Out': 0,
    'Water_Sensor': 0
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
    LIST_CITIES[1]: [
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

MAX_DISTANCE = 300
MIN_DISTANCE = 20
DISTANCE_INTERVAL = 2

MAX_HEIGHT = {
    LIST_CITIES[0]: 4000,
    LIST_CITIES[1]: 4000,
    LIST_CITIES[2]: 4000,
    LIST_CITIES[3]: 4000,
    LIST_CITIES[4]: 4000
}

MIN_HEIGHT = {
    LIST_CITIES[0]: -100,
    LIST_CITIES[1]: -100,
    LIST_CITIES[2]: -100,
    LIST_CITIES[3]: -100,
    LIST_CITIES[4]: -100
}

# -------------------------MAIN RIVER CONSTANTS-------------------------
INIT_WATER_HEIGHT = 0
WATER_INTERVAL = 30
WATER_HEIGHT_CONSTANT = 1

FLOW_MESSAGE = {
    'out':      b"K1\nL0\n",
    'in':       b"K0\nL1\n",
    'steady':    b"K0\nL0\n"
}
