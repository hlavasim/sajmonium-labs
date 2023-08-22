# sajmonium-labs

## Roadmap to IoT
* Current setup
  * ESP8266+DHT11 (Temperature + Humidity) => see file [iot/ESP8266_DHT11.ino](iot/ESP8266_DHT11.ino)
    * Board: NodeMCU 1.0 (ESP-12E Module)

* IoT Hub
  * InfluxDB
    * Bucket: sensor-data
    * Measurement: iot
    * Fields
      * temperature (in °C)
      * humidity (in %)
    * Tags
      * device (eg. ESP8266)
      * sensors (eg. DHT11)
      * SSIS (wifi name)
      * location (eg. home)
      * sublocation (eg. kitchen)

* Interesting sensors to look up
  * AS3935 - Lightning Detection
 
