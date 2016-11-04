import serial

s = serial.Serial("COM3", 9600)
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

s.write("Testing Write".encode("utf-8"));

while True:
    data = s.readline()
    print(data.decode("utf-8"))

s.close()
