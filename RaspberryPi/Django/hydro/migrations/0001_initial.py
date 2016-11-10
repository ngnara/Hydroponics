# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2016-11-09 05:52
from __future__ import unicode_literals

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='SensorLog',
            fields=[
                ('id', models.AutoField(primary_key=True, serialize=False)),
                ('date', models.DateTimeField(default=django.utils.timezone.now)),
                ('temp', models.FloatField()),
                ('humid', models.FloatField()),
                ('light', models.IntegerField()),
                ('ph', models.FloatField()),
            ],
        ),
    ]
