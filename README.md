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
      * rssi
    * Tags
      * device (eg. ESP8266)
      * sensors (eg. DHT11)
      * SSIS (wifi name)
      * location (eg. home)
      * sublocation (eg. kitchen)
     
* Roadmap
  * Gather data
    * Get better sensors for Temperature, Humidity (DHT22?)
    * Do I need barometric presure? (BME280)
    * CO2 sensor?
    * Another sensor?
    * Build 3 "all-in-one" devices and put them in workroom, living room, bed room
  * Battery
    * LiFePo4 32700 - 6000+ mAh - https://www.resacs.cz/baterie-lifepo4-3-2v-6000mah-32650/?gclid=Cj0KCQjw0IGnBhDUARIsAMwFDLmcR5s0ahfYannYUwTRQj9DR1x8X7hZTWs-gOWbLdSvazN1HTIGnl8aAv9nEALw_wcB
    * LiFePo4 protection - https://www.laskakit.cz/ochrana-lifepo4-baterie-1s-12a/
    * Get battery holder for 32700
    * Get charger - https://www.sportlampa.cz/LiitoKala-Lii-D4XL-21700-nabijecka-baterii-Pro-vel?gclid=Cj0KCQjw0IGnBhDUARIsAMwFDLk_VHRBoHL_fZ8C-mHqKeCsN-v3bHF1QiYDrFKi39xAKbFNnuS_LLMaAprrEALw_wcB

* Interesting sensors to look up
  * AS3935 - Lightning Detection
 
* Links
  * Aliexpress
  * https://dratek.cz/
  * https://www.laskakit.cz/
