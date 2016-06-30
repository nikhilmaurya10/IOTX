
#include <WiFi.h>
#define l_LED RED_LED
#define ul_LED GREEN_LED
#define con_LED YELLOW_LED
// your network name also called SSID
char ssid[] = "YOUR_WIFI_SSID";
// your network password
char password[] = "YOUR_PASSWORD";

//Device status...locked=0, unlocked=1
int stat=0;

String clientBuffer="";
String cb="";
String pass="";
char key[5];
char id[5];
String idd="";

// Initialize the Wifi client library
WiFiClient client;

// server address:
IPAddress server(xxx,xxx,xxx,xxx);
//pushbutton pin
const int buttonPin = PUSH2;
//int to hold button state
int buttonState = 0; 

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
  
  
    //setting button input
  pinMode(buttonPin, INPUT_PULLUP); 
  //setting pin direction for led....l_LED=Red....ul_LED=Green
  pinMode(l_LED, OUTPUT);  
  pinMode(ul_LED, OUTPUT);
  pinMode(con_LED, OUTPUT);  
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  // We are connected and have an IP address.
  // Print the WiFi status.
  printWifiStatus();
}

void loop() 
{  digitalWrite(con_LED, LOW);
  buttonState = digitalRead(buttonPin);
  locked();
  //check if device is locked and user wants to open it by pressing the button
  if (stat==0 && buttonState==1)
  { Serial.println("Enter your ID");
    delay(500);
    digitalWrite(con_LED, HIGH);
    delay(500);
    digitalWrite(con_LED, LOW);
    delay(500);
    digitalWrite(con_LED, HIGH);	//just to blink the led and wait some time while user enters the id
    delay(500);
    digitalWrite(con_LED, LOW);		
    delay(500);
    digitalWrite(con_LED, HIGH);
    delay(1000);
    digitalWrite(con_LED, LOW);
    
    
    // flush serial to read new key entered by user
    Serial.flush();
    //read key from serial and store into msg
    Serial.readBytes(id,5);
    for (int k=0;k<5;k++){
      idd+=id[k];
    }
    Serial.println("Entered ID is:");
    Serial.println(idd);
	
    // Request the password by sending the unique ID
    passRqst();

    //Get the key(OTP) from User
    Serial.println("Enter the key to open");
    delay(7000);
    // flush serial to read new key entered by user
    Serial.flush();
    //read key from serial and store into msg
    Serial.readBytes(key,5);
    for (int k=0;k<5;k++){
      pass+=key[k];
    }
    Serial.println("entered:");
    Serial.println(pass);
    digitalWrite(con_LED, HIGH);
    
    //retrieve key recieved from server will be saved in ariable cb
    //Serial.println("password is:");
    //Serial.println(cb);

      if(pass==cb){
      
      unlocked();

      delay(5000);
      }
	
	
    cb="";		//clear both variable for next session
    pass="";


  }

}


void passRqst(){
  httpRequest();
  char c;
  while (client.available()) {
   // Serial.print("*.");
    c = client.read();
   // Serial.write(c);
    clientBuffer+=c;

  }
   // Serial.println(cb);

  int len = clientBuffer.length();
  if(clientBuffer){
    for (int j=6;j>=2;j--){
      cb+=clientBuffer[len-j];
    }
    Serial.println("PIN");
    Serial.println(cb);
    //Serial.println(cb.length());
    clientBuffer="";

  }
  


  // if ten seconds have passed since your last connection,
  // then connect again and send data:

    
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server,1234)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    String get = "GET /id/";
    get+=idd;
    get+="/ HTTP/1.1";
    Serial.println(get);
    client.println(get);
//    client.println("Host: www.energia.nu");
//    client.println("User-Agent: Energia/1.1");
    //client.println("Connection: close");
    client.println();

  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
  idd="";
  delay(1000);
}

//function to start red LED to show device is locked
void locked()
{
  digitalWrite(ul_LED, LOW);
  digitalWrite(l_LED, HIGH);
}
// Turns on green LED to show its unlocked
void unlocked()
{
  digitalWrite(l_LED, LOW);
  digitalWrite(ul_LED, HIGH);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
