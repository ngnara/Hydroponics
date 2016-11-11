from django.shortcuts import render
from django.http import HttpResponse
from .models import SensorLog
import json;

# Create your views here.

def ajaxStatus(request):
    log = SensorLog.objects.all()[:1].order_by('date')
    jsonData = { "Temp" : log.temp, "Humid" : log.humid, "Light" : log.light, "pH" : log.ph }
    jsonString = json.dumps(jsonData)
    return HttpResponse(jsonString, content_type="application/json")
