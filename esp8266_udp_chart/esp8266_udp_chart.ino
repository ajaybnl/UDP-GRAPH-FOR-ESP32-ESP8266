/*Created by Ajay Kumar (ajaybnl@gmail.com) Youtube: Ajay Sudhera
   
   Check My Yourtube Video for How to View UDP Graph :
  https://www.youtube.com/watch?v=ssz-ebdW3ss

   This example shows how to connect and send data to you PC (To TelemetryViewer)
*/

#include <ESP8266WiFi.h>
#include <WiFiudp.h>


const char* ssid = "FILL_HERE";
const char* password = "FILL_HERE";

WiFiUDP udp;


//(Set your Static IP ADDRESS in your PC for Ease)



// Your PC IP ADDRESS
IPAddress udpAddress(10, 0, 0, 30); // Either 192.168.1.2 or anthing (Check Wifi Status)

unsigned int udpPort = 8080;  // port to connect


unsigned int udplocalport = 3424; //not needed to change


//Change to enable/disable serial
#define DEBUG 1   //0 for disabling


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected");

    udp.begin(udplocalport); //8080 port

    Serial.printf("Client IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), udplocalport);
  } else {
    Serial.println("Cannot Connect To WIfi");
  }
}




void loop()
{
  char text[50];
  
//Check Wifi Status
  if (WiFi.status() == WL_CONNECTED) {


    udp.begin(udplocalport);
    delay(10);

    //Connect To IP
    if (udp.beginPacket(udpAddress, udpPort) == 0) {
      udp.stop();
      Serial.println("UDP Connection Failed");
    } else {


      //Data to Send
      int var1 = analogRead(A0);
      int var2 = sin(var1)*100;


      //       Data,size
      snprintf(text, 50, "%d,%d\n", var1, var2);
      //You can add as many variables by putting a comma and \n at end of line



      //Send
      udp.printf(text);


      /* OR
        udp.write(text);
            udp.write("\n");

            //Or 
            udp.println(text);
            
      */


      udp.endPacket();

      Serial.println("UDP Connection Sucessful");
    }
    delay(1000);
  }

}
