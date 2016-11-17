from django.db import models
from django.utils import timezone

class SensorLog(models.Model):
    id = models.AutoField(primary_key=True)
    date = models.DateTimeField(default=timezone.now)
    temp = models.FloatField()
    humid = models.FloatField()
    light = models.IntegerField()
    ph = models.FloatField()

    def __str__(self):
        return self.id

class SettingsLog(models.Model):
    id = models.AutoField(primary_key=True)
    interval = models.IntegerField()
    fan_in_speed = models.IntegerField()
    fan_out_speed = models.IntegerField()
