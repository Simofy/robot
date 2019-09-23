import serial, time, PySimpleGUI as sg
import threading
import sys


def logging_arduino():
    while True:
        data = arduino.readline()
        if data:
            print(data)


layout = [[
    sg.Text('Rotate: '),
    sg.Slider((0, 180), 50, orientation='horizontal')
], [sg.Button('Read'), sg.Exit()]]
window = sg.Window('Demo', layout)
arduino = serial.Serial('COM7', 9600, timeout=.1)
time.sleep(1)  #give the connection a second to settle

logger = threading.Thread(target=logging_arduino)
logger.start()

while True:
    event, values = window.read()
    sg.Print(event, values[0])

    if event in (None, 'Exit', 'Cancel'):
        break
logger._stop()
window.close()
