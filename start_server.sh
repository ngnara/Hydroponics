#!/bin/bash

python3 /Server/Serial_Server.py &
python3 /Server/manage.py runserver 0.0.0.0:80
