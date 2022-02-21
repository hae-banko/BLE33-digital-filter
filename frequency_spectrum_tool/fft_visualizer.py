"""----------------------------------------------------
Fast Fourier Transform Visualizer 
Autor: Irvan Rizqullah Fikardi

Kontext: 
Dieser Modul nimmt Sensordaten aus Arduino BLE-33 Sense
(Accelerometer, Gyroskop, und Magnetometer) und erzeugt
mit schnellem Fourier-Transformation ein Frequenzspektrum 
fuer die Identifikation von bestimmten Frequenzbereich, 
mit dem man Frequenz des Rauschen identifizieren kann.

Format des Eingabedatei (Wenn nicht gleich, bitte die Benennung aendern):
a_X:WERT a_Y:WERT a_Z:WERT m_X:WERT m_Y:WERT m_Z:WERT g_X:WERT g_Y:WERT g_Z:WERT

1.) 'a' fuer Accelerometer; 'm' fuer Magnetometer; 'g' fuer Gyroskop
2.) Unterstreichenzeichen zwischen Sensorart und Achsen
3.) Achsen mit Kapitalzeichen geschrieben
4.) Jeder Variaber wird mit einem Leerzeichen separiert
5.) Anordnung der Variablen sind festgestellt, bei Aenderung muss
man noch mal mit dem Code anpassen.

---------------------------------------------------"""
import numpy             as np
import matplotlib.pyplot as plt
import scipy.fftpack
import os 

# Abtastrate sind im LSM9DS1.h gegeben
ACC_SAMPLE_RATE  = 119.0 
GYRO_SAMPLE_RATE = 119.0 
MAGN_SAMPLE_RATE = 20.0 
a_X = []
a_Y = []
a_Z = []
g_X = []
g_Y = []
g_Z = []
m_X = []
m_Y = []
m_Z = []

data_list       = [a_X, a_Y, a_Z, g_X, g_Y, g_Z, m_X, m_Y, m_Z]
sample_rate     = [ACC_SAMPLE_RATE, GYRO_SAMPLE_RATE, MAGN_SAMPLE_RATE]
names_to_filter = ['a_X','a_Y', 'a_Z', 'g_X','g_Y', 'g_Z', 'm_X','m_Y', 'm_Z']

# Pfad setzen
ROOT_DIR = os.path.dirname(os.path.abspath(__file__))
DATA_LOG_PATH = ROOT_DIR + "\\" + "sensor_data_log.txt"

# Daten extrahieren und kategorisieren
fp = open((DATA_LOG_PATH), 'rt')
with fp as SENSOR_LOG:
    for raw_line in SENSOR_LOG:
        raw_line = raw_line.rstrip('\n')
        if raw_line == ['']: # Skips empty lines
            continue
        splitted_variables = raw_line.split(" ")
        for i in range(9): # 9-Achsen
            data_list[i].append(float(splitted_variables[i][4:]))

# Output test
"""
i = 0
for each in data_list:
    print(names_to_filter[i], end='')
    print(each)
    i += 1
"""

# Fast Fourier Transformation


"""TODO"""
# Renew main.ino so that it will conform to the format that has been set in sensor data log
# FFT
# Export as image 


