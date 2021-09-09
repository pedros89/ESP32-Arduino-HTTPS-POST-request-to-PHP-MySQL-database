# ESP32-Arduino-HTTPS-POST-request-to-PHP-MySQL-database
Send data via POST to a PHP script on your HTTPS server and insert the data in MySQL database. Coded with Arduino.

Make sure you have all the following info:
- Wifi name
- Wifi password
- the HTTPS certificate for your website.  [Link to know more](https://www.esri.com/arcgis-blog/products/bus-analyst/field-mobility/learn-how-to-download-a-ssl-certificate-for-a-secured-portal/)
- Database info: database servername, database name, user, password 

Make sure you create with phpMyAdmin a new table in your database, for example sensor_reading.

The database table should have the following structure:

| Variable Name | Variable Type | Additional info  	|
| ------------- |:-------------:| ---------------------:|
| id (Primary)  | int(11) 	| AUTO_INCREMENT	|
| user      	| text      	| latin1_swedish_ci 	|
| temperatureC  | int(11)      	|     			|
| temperatureF  | int(11)      	|     			|
| date   	| date      	|     			|
| hour   	| time      	|     			|
		         

I wrote this code getting pieces of code from the official [Basic HTTPS client example](https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/examples/BasicHttpsClient/BasicHttpsClient.ino)

and from [Techtutorials blog](https://techtutorialsx.com/2017/05/20/esp32-http-post-requests/)

