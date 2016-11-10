import serial
import json
import os
import sys
import platform
import pymysql
pymysql.install_as_MySQLdb()

#외부에서 장고 프레임워크 불러오기
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "gui.settings")
os.environ["DJANGO_SETTINGS_MODULE"] = "gui.settings"
import django
django.setup()

from hydro.models import SensorLog

def handshakeSerial(s):
    while True:
        data = s.read()
        if data == b'C' :
            print("아두이노에서 확인 바이트를 받았습니다.")
            break

    s.write(b'R')
    print("아두이노에게 응답 바이트를 보냈습니다.")

    while True:
        data = s.read()
        if data == b'R' :
            print("아두이노가 응답 바이트를 받았다고 보냈습니다.")
            break

i = 0
while True:
    #운영체제별 포트 결정
    port = ""
    if platform.system == "Windows":
        port = "COM" + str(i + 2)
    else:
        port = "/dev/ttyACM" + str(i)

    # try:
    with serial.Serial(port, 9600) as s:
        print("현재 포트는" + s.name)
        handshakeSerial(s)

        while True:
            data = s.readline()
            jsonData = json.loads(data)
            print(jsonData)

            log = SensorLog.objects.create(temp=jsonData['Temp'], humid=jsonData['Humid'], light=jsonData['Light'], ph=jsonData['pH'])
    # except:
    #     print(port + "포트는 실패하였습니다. 다시 검색합니다.")
    #     i = i+1
