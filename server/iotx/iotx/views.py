from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt
from post_office import mail
import random
import urllib2

from .models import LUser

# Home function to display the landing page
def home(request):
	return render(request,'iotx/home.html',{})

# The function returns a key when you visit http://127.0.0.1/get
def index(request):
	password=random.randrange(10000, 99999, 2)
	return JsonResponse({'key':password})

# This function implements the Email and sms facilities. It takes id of user and uses perdefined email and phone no for the user
def detail(request, iid):
	password=random.randrange(10000, 99999, 2)
	user=LUser.objects.get(userID=iid)
	phone_no=user.phone
	#URL for SMS serive.
	url='http://cloud.smsindiahub.in/vendorsms/pushsms.aspx?user=your_user_name&password=enter_your_pass&msisdn='+str(phone_no)+'&sid=WEBSMS&msg=PIN'+str(password)+'&fl=0'
	# Simply opening the url will send SMS
	result = urllib2.urlopen(url).read()
	# Check if user is valid
	if user:
		
		mail.send(
    		user.email, # List of email addresses also accepted
    		'redrobin9211@gmail.com',
   		 	subject='HomeKEY',
    		message=password,
    		html_message='Hi <strong>there</strong>! Your PIN is '+str(password),
    		# priority='now',
			)
	
	return JsonResponse({'key':password})


