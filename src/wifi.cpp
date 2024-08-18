#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <_env.h>
#include "wifi.h"

WiFiServer webserver(80);
WiFiMulti wifiMulti;
const uint32_t connectTimeoutMs = 1000;
String WifiSSID = "";
IPAddress WifiIP = IPAddress(0, 0, 0, 0);

void connectToWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(ENV_HOSTNAME);
    WiFi.disconnect();

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    Serial.println("scan done");
    bool network_found = false;
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            if (WiFi.SSID(i) == ENV_WIFI_SSID)
                network_found = true;
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
        }
    }
    Serial.println("");

    //@TODO: add extra SSIDs if required.
    // wifiMulti.addAP(ENV_WIFI_SSID, ENV_WIFI_PASSPHRASE);
    // wifiMulti.addAP(ENV_WIFI_SSID2, ENV_WIFI_PASSPHRASE2);

    wifiMulti.addAP(ENV_WIFI_SSID, ENV_WIFI_PASSWORD);
    Serial.print(" WifiMulti Adding WIFI Network: ");
    Serial.print(ENV_WIFI_SSID);
  

    Serial.println("Connecting Wifi...");
    if (wifiMulti.run() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.print("WiFi connected: ");
        Serial.println(WiFi.SSID());
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        WifiSSID = WiFi.SSID();
        WifiIP = WiFi.localIP();
        webserver.begin();
    }
}