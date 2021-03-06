# -*- coding: utf-8 -*-
# Generated by Django 1.9.5 on 2016-04-09 00:21
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='LUser',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('pub_date', models.DateTimeField(verbose_name=b'date published')),
                ('userID', models.IntegerField()),
                ('email', models.EmailField(max_length=255, unique=True, verbose_name=b'email address')),
                ('is_active', models.BooleanField(default=True)),
            ],
        ),
    ]
