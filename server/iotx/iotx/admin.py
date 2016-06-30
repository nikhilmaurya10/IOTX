from django.contrib import admin

from .models import LUser
# Registering admin site to add and remove user
admin.site.register(LUser)