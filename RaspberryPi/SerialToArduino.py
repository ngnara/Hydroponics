import serial
import json;

with serial.Serial("/dev/ttyACM1", 9600) as s :
    #s = serial.Serial("/dev/ttyACM0", 9600)
    print("Port name : " + s.name)

    while True:
        data = s.read()
        if data == b'C' :
            print("Connecting byte received.")
            break

    s.write(b'R')

    while True:
            data = s.read()
            if data == b'R' :
                print("Arduino connected.")
                break

    s.write(b'{\"Comm\" : \"setInterval\", \"Interval\" : 1000 }')
    while True:
        data = s.readline()
        print(data)
