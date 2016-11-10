from django.shortcuts import render
from django.http import HttpResponse
from .models import SensorLog
import json;

# Create your views here.

def ajaxStatus(request):
    log = SensorLog.objects.all()[:1].order_by('date')
    log.temp
