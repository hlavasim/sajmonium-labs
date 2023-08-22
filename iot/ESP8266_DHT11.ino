#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
  #elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
  #endif
  
  #include <InfluxDbClient.h>
  #include <InfluxDbCloud.h>
  #include "DHT.h"  
  
  // WiFi AP SSID
  #define WIFI_SSID "<Wifi SSID>"
  // WiFi password
  #define WIFI_PASSWORD "<Wifi Password>"
  
  #define INFLUXDB_URL "http://<Influx IP>:<Influx PORT>"
  #define INFLUXDB_TOKEN "<Influx TOKEN>"
  #define INFLUXDB_ORG "<Influx  ORG>"
  #define INFLUXDB_BUCKET "<Influx Bucket>"

  #define INFLUXDB_TAG_LOCATION "home"
  #define INFLUXDB_TAG_SUBLOCATION "workroom"
  #define INFLUXDB_TAG_SENSORS "DHT11"
  
  // Time zone info
  #define TZ_INFO "UTC2"
  
  // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  
  // Declare Data point
  Point sensor("iot");
  DHT dht2(2,DHT11);  
  
  void setup() {
    Serial.begin(9600); 
    dht2.begin();

  
    // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  
    Serial.print("Connecting to wifi");
    while (wifiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
    Serial.println();
  
    // Accurate time is necessary for certificate validation and writing in batches
    // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
    // Syncing progress and the time will be printed to Serial.
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  
  
    // Check server connection
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }

    // Add tags to the data point
    sensor.addTag("device", DEVICE);
    sensor.addTag("sensors", INFLUXDB_TAG_SENSORS);
    sensor.addTag("SSID", WiFi.SSID());
    sensor.addTag("location", INFLUXDB_TAG_LOCATION);
    sensor.addTag("sublocation", INFLUXDB_TAG_SUBLOCATION);
  }

void loop() {
    // Clear fields for reusing the point. Tags will remain the same as set above.
    sensor.clearFields();
  
    // Store measured value into point
    // Report RSSI of currently connected network
    sensor.addField("rssi", WiFi.RSSI());

    // Temperature
    sensor.addField("temperature", dht2.readTemperature( ));

    // Humiduty
    sensor.addField("humidity", dht2.readHumidity());

  
    // Print what are we exactly writing
    Serial.print("Writing: ");
    Serial.println(sensor.toLineProtocol());
  
    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }
  
    // Write point
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  
    Serial.println("Waiting 60 second");
    delay(60000);
  }
