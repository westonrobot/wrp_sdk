# Weston Robot Platform SDK (wrp_sdk)

## Table of Contents
- [Weston Robot Platform SDK (wrp\_sdk)](#weston-robot-platform-sdk-wrp_sdk)
  - [Table of Contents](#table-of-contents)
  - [Description](#description)
  - [Features](#features)
    - [Supported Platforms](#supported-platforms)
    - [Supported Robot Bases](#supported-robot-bases)
    - [Supported Peripherals](#supported-peripherals)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Contact](#contact)
  - [FAQ](#faq)


## Description
wrp_sdk provides C++ interface to mobile robot bases and robot peripherals (IMU, Ultrasonic, GPS, Camera Lift, etc.) from Weston Robot.

wrp_sdk is provided as a **Debian installation package** only and you can install it by following the steps given below. For sample code, please check the appropriate version tags of this repository. 

## Features
### Supported Platforms
- Ubuntu 20.04 LTS (Focal Fossa): x86_64, arm64
- Ubuntu 22.04 LTS (Jammy Jellyfish): x86_64, arm64

### Supported Robot Bases
- AgileX Robot Bases using AgileX Robotics' V2 Protocol
- Mobile Bases using Weston Robot's zbus Protocol

### Supported Peripherals
- Serial GPS Receivers using NMEA Protocol.
- Hipnuc IMU Sensors.
- Dyp Ultrasonic Sensors.
- [Weston Robot's Power Regulator V2](https://docs.westonrobot.net/periph_user_guide/westonrobot/power_regulator_v2.X.html)

## Installation
* Install Dependencies
  * [LelyCAN](https://opensource.lely.com/canopen/docs/installation/).
    * Required by the peripheral drivers, only the robot base samples will be built if you don't install the dependencies.

* Add Weston Robot's APT repository to your system.
  * Please find the latest installation instructions from [this page](https://docs.westonrobot.net/software/installation_guide.html).

* Install wrp-sdk
```bash
$ sudo apt update
$ sudo apt install wrp-sdk
```

***Note:***  
"apt" will install the latest version of wrp_sdk by default. Weston Robot releases stable versions of the SDK regularly. In case your robot firmware is not compatible with the latest SDK, you can install older versions of the SDK manually.

For example, if your robot is only compatible with wrp_sdk up to v1.0.7, you can specify the version you want to install

```
$ sudo apt remove wrp-zbus wrp-sdk
$ sudo apt install wrp-sdk=1.0.7
```

You can also download compatible wrp_sdk and wrp_zbus debian installation packages from [Releases](https://github.com/westonrobot/wrp_sdk/releases). Please contact us at [support@westonrobot.com](mailto:support@westonrobot.com) if you're not sure which version of the SDK you should use.

## Usage
Sample code demos are provided in the [sample folder](./sample/).

To build the sample code demos, please follow the instructions below after installing the SDK (and dependencies).
```
$ mkdir build && cd build
$ cmake ..
$ make -j8
```
You will get executable "sample_xxx" inside the build/bin folder.

## Contact
Please contact us at [support@westonrobot.com](mailto:support@westonrobot.com).
Documentation of the various robots are available at [docs.westonrobot.net](https://docs.westonrobot.net).

## FAQ
* **Q1:** What's the difference between [ugv_sdk](https://github.com/westonrobot/ugv_sdk) and wrp_sdk?

    **A1**: **ugv_sdk** provides a C++ interface to mobile robot bases manufactured by AgileX Robotics. It's a joint effort by Weston Robot and Agilex Robotics development teams. Robots compatible with ugv_sdk talk the AgileX Procotocol (V1 and V2) on the CAN bus. 
    **wrp_sdk** provides a C++ interface to both robot bases and peripherals supported by Weston Robot. It allows users to use a single unified interface to control all different kinds of mobile robots (e.g. wheeled/tracked/legged robots), including but not limited to the ones from AgileX. It is also the foundation of the various robotics software toolboxes developed by Weston Robot (e.g. the Robot Maintenance Toolbox, the Assisted Driving Toolbox).