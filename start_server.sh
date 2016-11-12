#!/bin/bash

if [ "$UID" -ne "0" ]
then
echo "루트 권한으로 실행시켜주세요."
exit 67
fi

python3 /Server/Serial_Server.py &
python3 /Server/manage.py runserver 0.0.0.0:80
