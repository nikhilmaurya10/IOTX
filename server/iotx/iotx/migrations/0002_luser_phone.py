# -*- coding: utf-8 -*-
# Generated by Django 1.9.5 on 2016-04-11 07:38
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('iotx', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='luser',
            name='phone',
            field=models.CharField(default=9555883435L, max_length=10),
        ),
    ]
