from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.

class status(request):
    return render(request, 'hydro/status.html', {})

class ajax_status(request):
    return HttpResponse()
