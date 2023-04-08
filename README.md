# twinThingPicoWExample
Example of IoT MQTT Framework for RPI PicoW. [twinThingPicoW](https://github.com/jondurrant/twinThingPicoW)

Also see the Python library and Twin Manager - [TwinThingPyMQTT](https://github.com/jondurrant/TwinThingPyMQTT)


## Twin

A simple Thing that models an RGB Lamp. It contains the following attributes:

+ temp: Float Temperature in celcius reported by the Pico-W
+ boot: Int Seconds since the device booted
+ rgb: Array of Ints. The Red, Green and Blue components of the lamp colour
+ on: Bool if the lamp is on or off

A RGB status LED showing the state of the device connection to GP2, GP4 and GP5 (RGB). These are defined in main.cpp.
No connection is Red, Connection to Wifi is Green, Connection to MQTT is Blue. Amber is
authentication error.

The RGB Lamp is another RGB LED on GP6, GP8, and GP9. These are defined in main.cpp.

Each LED is connected to ground via a 90ohm resistor.

## TwinTLS

This is the same examples but using a TLS secured socket for communication. This uses [WolfSSL](https://www.wolfssl.com/) to handle the secure socket.


## MQTT Topics

The example responds or publishes the following topic. Where <clientID> is the client
ID set for the device.

### Ping

+ GRP/ALL/TPC/PING Subscribes: Will respond on PONG topic below with what ever was provided as a parameter
+ TNG/<clientId>/TPC/PING Subscribes: Will respond on PONG topic below with what ever was provided as a parameter
+ TNG/<clientId>/TPC/PONG Publishes: Publish response to a ping

### State management

+ TNG/<clientId>/STATE/SET Subscribe: Set or update the state. 
+ TNG/<clientId>/STATE/GET Subscribe: Request publication of full state
+ TNG/<clientId>/STATE/UPD Publish:	publishes state change delta updates or full state of device

Set the define full state by sending JSON messahe of the form:
```
{'state':{
    'on': True,
    'rgb': [0xFF, 0x00, 0xFF]
    }
}
```

Update by using the form:
```
{'delta':{
    'on': True,
    'rgb': [0xFF, 0x00, 0xFF]
    }
}
```

The same formate structure is used for the published messages on the UPD topic.

### Examples
Example publication of Set and Get messages in python are in the "py" folder

## Compilation
To avoid putting credentials into make files of python scrips these are read from environment variables.
The following environment variables therefore need to be defined:
+ MQTT_CLIENT Client ID for the device or client
+ MQTT_USER Username for MQTT authentication
+ MQTT_PASSWD Password for MQTT authentication - must be provided but can be blank
+ MQTT_HOST MQTT broker host address
+ MQTT_PORT broker port number, normally 1883 or 8883
+ WIFI_SSID wifi service ID to connect to
+ WIFI_PASSWORD WIFI service password

For either of the two examples to compile:
1. mkdir build
2. cd build
3. cmake ..
4. make








