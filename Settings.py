# Connection_Settings
BT_PORT_NAME = '/dev/cu.usbmodem142401'
# BT_PORT_NAME = '/dev/ttyACM0'

# ENCODING DATA
ENCODER_DC = {
    'A': 'encoder_day',
    'B': 'encoder_year',
    'C': 'encoder_month',
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

LIST_CITIES = ["Rotterdam", "Arnhem", "Amsterdam", "Maastricht", "Utrecht"]
LIST_CITIES_SENSOR = ["Rotterdam",  "Utrecht", "Arnhem", "Maastricht", "Amsterdam"]
# LIST_CITIES = ["Rotterdam", "Driel boven", "IJmuiden Noordersluis", "Maastricht", "Utrecht"]

CONVERT_TO_CITY_DC = {
    'distance_A': LIST_CITIES[0],
    'distance_B': LIST_CITIES[1],
    'distance_C': LIST_CITIES[2],
    'distance_D': LIST_CITIES[3],
    'distance_E': LIST_CITIES[4]
}

# Headers used [A, B, C, D, E, F, G, H, I, J, K, L, M, N]
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

MESSAGES_LCD = {
    "City": b"M",
    "Date": b"N"
}

MAX_DISTANCE = 300
MIN_DISTANCE = 20

LED_AMOUNT = 8

DISTANCE_INTERVAL = 2

MAX_HEIGHT = {
    LIST_CITIES[0]: 240,
    LIST_CITIES[1]: 1300,
    LIST_CITIES[2]: 140,
    LIST_CITIES[3]: 4900,
    LIST_CITIES[4]: 700
}

MIN_HEIGHT = {
    LIST_CITIES[0]: -160,
    LIST_CITIES[1]: 50,
    LIST_CITIES[2]: -90,
    LIST_CITIES[3]: 3600,
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

LED_HEADERS = {
    LIST_CITIES[0]: b"Q",
    LIST_CITIES[1]: b"O",
    LIST_CITIES[2]: b"P",
    LIST_CITIES[3]: b"R",
    LIST_CITIES[4]: b"S"
}


colors = [
    b'255,0,16',
    b'255,0,0',
    b'255,10,0',
    b'255,20,0',
    b'255,30,0',
    b'255,40,0',
    b'255,50,0',
    b'255,60,0',
    b'255,70,0',
    b'255,80,0',
    b'255,90,0',
    b'255,100,0',
    b'255,110,0',
    b'255,120,0',
    b'255,130,0',
    b'255,140,0',
    b'255,150,0',
    b'255,160,0',
    b'255,170,0',
    b'255,180,0',
    b'255,190,0',
    b'255,200,0',
    b'255,210,0',
    b'255,220,0',
    b'255,230,0',
    b'255,240,0',
    b'255,250,0',
    b'253,255,0',
    b'215,255,0',
    b'176,255,0',
    b'138,255,0',
    b'101,255,0',
    b'62,255,0',
    b'23,255,0',
    b'0,255,16',
    b'0,255,54',
    b'0,255,92',
    b'0,255,131',
    b'0,255,168',
    b'0,255,208',
    b'0,255,244',
    b'0,228,255',
    b'0,212,255',
    b'0,196,255',
    b'0,180,255',
    b'0,164,255',
    b'0,148,255',
    b'0,132,255',
    b'0,116,255',
    b'0,100,255',
    b'0,84,255',
    b'0,68,255',
    b'0,50,255',
    b'0,34,255',
    b'0,18,255',
    b'0,2,255',
    b'0,0,255',
    b'1,0,255',
    b'2,0,255',
    b'3,0,255',
    b'4,0,255',
    b'5,0,255',
]
