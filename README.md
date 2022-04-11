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

**Note**: "apt-get" will install the latest version of wrp_sdk by default. Weston Robot releases stable versions of the SDK regularly. In case your robot firmware is not compatible with the latest SDK, you can install older versions of the SDK manually. For example,

```
$ sudo apt-get remove wrp_zbus
$ sudo apt-get install wrp_zbus=0.6.1
$ sudo apt-get install wrp_sdk=0.8.7
```

You can also download compatible wrp_sdk and wrp_zbus debian installation packages from [Releases](https://github.com/westonrobot/wrp_sdk/releases). Please contact us if you're not sure which version of the SDK you should use.

## Build the sample code

Please refer to the BUILD.md document in each "sample-*" branch for the building instructions.

## Q&A

* **Q1:** What's the difference between [ugv_sdk](https://github.com/westonrobot/ugv_sdk) and wrp_sdk?

    **A1**: **ugv_sdk** provides a C++ interface to mobile robot bases manufactured by AgileX Robotics. It's a joint effort by Weston Robot and Agilex Robotics development teams. Robots compatible with ugv_sdk talk the AgileX Procotocol (V1 and V2) on the CAN bus. 
    **wrp_sdk** provides a C++ interface to both robot bases and peripherals supported by Weston Robot. It allows users to use a single unified interface to control all different kinds of mobile robots (e.g. wheeled/tracked/legged robots), including but not limited to the ones from AgileX. It is also the foundation of the various robotics software toolboxes developed by Weston Robot (e.g. the Robot Maintenance Toolbox, the Assisted Driving Toolbox).