#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


const char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n"\
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"\
"DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n"\
"PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n"\
"Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"\
"AN+v6ZdQCINXtMxiZfaQeeeH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n"\
"rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n"\
"OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n"\
"xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n"\
"7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n"\
"aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDeeeTAQH/BAUwAwEB/zAOBgNV\n"\
"HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n"\
"SIb3DQEwerUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n"\
"ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n"\
"AvHRAosZy5Q6XkjEGB5YGV8eAlrwDrewrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n"\
"R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n"\
"JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n"\
"Ob8VZRzI9neWagqNdwvYkQsEjgfeftYK7p2CNTUQ\n"\
"-----END CERTIFICATE-----\n";


WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("YOUR WIFI NAME HERE", "YOUR WIFI PASSWORD HERE");

  // wait for WiFi connection
  Serial.print("Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

}

void loop() { 
  
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(rootCACertificate);

    {
      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, "https://www.yourWebsiteHere.com/esp32postRequest.php")) {  // HTTPS
        
        /*start POST*/
        https.addHeader("Content-Type", "application/x-www-form-urlencoded");             //Specify content-type, in the case it was a GET request it would be  "text/plain"
        int httpResponseCode = https.POST("temp=20&tempF=68");                            //Send the actual POST request, for example send Temperature both in C?? and in F??
        
         if(httpResponseCode>0){
           String response = https.getString();                       //Get the response to the request
           Serial.println(httpResponseCode);                          //Print return code
           Serial.println(response);                                  //Print request answer
         }else{
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);         
           }

        /*end POST*/
        
        https.end();
      
      
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }

    
    }
  
    delete client;
  } else {
    Serial.println("Unable to create client");
  }

  Serial.println();
  Serial.println("Waiting 10s before the next round...");
  delay(10000);
}
