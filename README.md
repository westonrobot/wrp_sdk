# Weston Robot Platform SDK (wrp_sdk)

wrp_sdk provides C++ interface to mobile robot bases and robot peripherals (IMU, Ultrasonic, GPS, Camera Lift, etc.) from Weston Robot. wrp_sdk is provided as a **Debian installation package** only and you can install it by following the steps given below. For sample code, please check the "sample-*" branches of this repository. 

## Supported platforms

* OS: Ubuntu 18.04, Ubuntu 20.04
* Architecture: x86_64, arm64

## Install the SDK

```
echo "deb https://westonrobot.jfrog.io/artifactory/wrtoolbox-release $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/weston-robot.list
curl -sSL 'https://westonrobot.jfrog.io/artifactory/api/security/keypair/wr-deb/public' | sudo apt-key add -
sudo apt-get update
sudo apt-get install wrp_sdk
```

**Note**: "apt-get" will install the latest version of wrp_sdk by default. Weston Robot releases stable versions of the SDK twice a year. In case your robot firmware is not compatible with the latest SDK, you can install older versions of the SDK manually. For example,

```
$ sudo apt-get remove wrp_zbus
$ sudo apt-get install wrp_zbus=0.6.1
$ sudo apt-get install wrp_sdk=0.8.7
```
Please contact us if you're not sure which version of the SDK you should use.