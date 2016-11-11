from django.shortcuts import render
from django.http import HttpResponse
from .models import SensorLog
import json;

# Create your views here.

def ajaxStatus(request):
    log = SensorLog.objects.all().latest('date')
    jsonData = { "Temp" : log.temp, "Humid" : log.humid, "Light" : log.light, "pH" : log.ph, "Date" : str(log.date.astimezone()) }
    jsonString = json.dumps(jsonData)
    return HttpResponse(jsonString, content_type="application/json")
