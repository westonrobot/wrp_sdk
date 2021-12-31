# Weston Robot Platform SDK (wrp_sdk)

wrp_sdk provides C++ interface to mobile robot bases and robot peripherals (IMU, Ultrasonic, GPS, Camera Lift, etc.) from Weston Robot. wrp_sdk is provided as a Debian installation package and you can install it by following the steps given below. For sample code, please check the "sample-*" branches of this repository. 

## Supported platforms

* OS: Ubuntu 18.04, Ubuntu 20.04
* Architecture: x86_64, arm64

## Install the SDK

```
sudo apt-get install libglfw3-dev libyaml-cpp-dev libopencv-dev
echo "deb https://westonrobot.jfrog.io/artifactory/wrtoolbox-release $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/weston-robot.list
curl -sSL 'https://westonrobot.jfrog.io/artifactory/api/security/keypair/wr-deb/public' | sudo apt-key add -
sudo apt-get update
sudo apt-get install wr_assisted_teleop
```
