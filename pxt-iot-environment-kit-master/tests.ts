ESP8266_IoT.connectWifi(
SerialPin.P8,
SerialPin.P12,
BaudRate.BaudRate115200,
"your_ssid",
"your_pw"
)
basic.forever(function () {
    ESP8266_IoT.connectThingSpeak(
    "api.thingspeak.com",
    "your_write_api_key",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
    )
})