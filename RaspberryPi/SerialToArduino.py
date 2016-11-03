import serial;

s = serial.Serial("/dev/ttyUSB0", 9600)
print(s.name)

while True:
    data = s.read()
    if data == b'C' :
        print("Received")
        break

s.write(b'R')

while True:
        data = s.read()
        if data == b'R' :
            print("Connected")
            break

while True:
    data = s.readline()
    print(data)

s.close()
