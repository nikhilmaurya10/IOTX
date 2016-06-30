#IOTX - Smart Lock


A Smart Lock System based on Texas Instruments' CC3200 Launchpad which uses randomly generated password to give temporary access. A Django based server is used to add users. Phone number and Email of user is registered and used to generate OTP which is emailed sent to phone and to the CC3200 too, but first the user is need to be registered and he will get a unique ID which he would need to use every time to get an OTP. RED and GREEN LEDs are used to indicate locking and opening of locks. No external keypad or display is required only the Launchpad. We will use Energia IDE Serial Monitor to interact with our Board, i.e. Enter User ID and password.



## Installation

This project uses two technologies
1. Python-Django
2. Energia Sketch C++

### 1. Installing and running Django Server
To setup Django on your system follow this guide here:
	$ https://www.codingforentrepreneurs.com/projects/#setup	
Choose your OS and install everything. Install virtualenv in iotx/iotx folder.
Install requirements from requirements.txt file as follows:
	$ pip install -r requirements.txt

After everything is done edit the settings.py file to change username and password for email.
Also edit views.py (you can find both files in iotx/iotx/iotx) file and change the username and password in the URL for sending sms. You will have to make an account at smsindiahub.in you will get 10 free SMS. Replace the username and password in views.py file.

After all is done Create a superuser this will allow you to add Users at Django admin portal @ http://127.0.0.1/admin
	$ python manage.py createsuperuser
Enter username email and password.

Now Migrate or create date base by running
	$ python manage.py syncdb
Everythings done. Now to run the server anytime activate the run the command
	$ python manage.py runserver
the server will start running at http://127.0.0.1/ check this for a welcome page.


### Installing Energia IDE and setting up for the board.
This setup uses Energia IDE and its serial monitor is user to enter unique user pin as well as the OTP.
to install Energia visit 
	$ energia.eu
Open up the .ino sketch file with energia and edit these parameters
	$ ssid       -your WiFi SSID
	$ password	 -your WiFi Password
	$ IPAddress server(xx,xx,xx,xx)    -use the ip of machine where the django server is running.

Save the file Compile, Upload, Run and open up serial monitor it will show network its connected.
Press the push button enter the ID and hit ENTER on serial monitor. it will send the ID the the Django server(make sure its running).
the password will be genrated and sent. Enter the password and if this matches GREEN LED should light up. After few seconds RED LED will be turned on and green off showning and system is locked again.


## License
NO LICENCE. YOU ARE ELIGIBLE TO DO ANYTHING WITH THIS CODE. 