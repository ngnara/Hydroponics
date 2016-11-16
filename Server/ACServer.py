import serial
import json
import platform
import threading

#MySQL 라이브러리 불러오기
import pymysql
pymysql.install_as_MySQLdb()

#장고 프레임워크 라이브러리 불러오기
import os
import sys
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "gui.settings")
os.environ["DJANGO_SETTINGS_MODULE"] = "gui.settings"

import django
django.setup()

#장고 프레임워크 SensorLog 모델 불러오기
from hydro.models import SensorLog

#분석 및 제어 서버(Analysis & Control Server)
class ACServer:

    #쓰리웨이 핸드쉐이크
    def handshake(self):
        s = self.serial

        data = s.read()
        if data == b'C' : print("3-Way Handshake : SYN 데이터 수신")
        else : print("3-Way Handshake : 식별 불가 데이터")

        s.write(b'R')
        print("3-Way Handshake : SYN+ACK 데이터 송신")

        data = s.read()
        if data == b'R' : print("3-Way Handshake : ACK 데이터 수신")
        else : print("3-Way Handshake : 식별 불가 데이터")

    def __init__(self):
        numPort = 0
        while True:
            #운영체제별 포트 결정
            port = ""
            if platform.system == "Windows": port = "COM" + str(numPort + 2)
            else: port = "/dev/ttyACM" + str(numPort)

            try:
                with serial.Serial(port, 9600) as self.serial:
                    s = self.serial
                    print("현재 포트 : " + s.name)
                    self.handshake()

                    listen = ListenServer()
                    listen.s = self.serial
                    listen.start()
                    while True:
                        pass

            except serial.SerialException:
                if numPort <= 20 :
                    print(port + "포트 실패, 재 검색")
                    numPort = numPort + 1
                else :
                    print("연결된 포트를 찾을 수 없습니다.")
                    exit()

#수신 서버
class ListenServer(threading.Thread):

    def run(self):
        jsonData = json.loads(self.s.readline().decode("utf-8"))
        print(jsonData)

        log = SensorLog.objects.create( \
            temp = jsonData['Temp'], \
            humid =jsonData['Humid'], \
            light = jsonData['Light'], \
            ph = jsonData['pH'])

server = ACServer()
