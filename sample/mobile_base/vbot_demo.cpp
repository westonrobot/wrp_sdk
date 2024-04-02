/*
 * vbot_demo.cpp
 *
 * Created on: Jan 19, 2022 15:55
 * Description:
 *
 * Copyright (c) 2021 Weston Robot Pte. Ltd.
 */

#include <unistd.h>

#include <iomanip>
#include <sstream>
#include <iostream>

#include "wrp_sdk/mobile_base/westonrobot/mobile_base.hpp"

using namespace westonrobot;

std::string ConvertToString(double value) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << value;
  return stream.str();
}

int main(int argc, char **argv) {
  std::string device_name;

  if (argc == 2) {
    device_name = {argv[1]};
    std::cout << "Specified CAN: " << device_name << std::endl;
  } else {
    std::cout << "Usage: sample_vbot_demo <interface>" << std::endl
              << "Example 1: ./sample_vbot_demo can0" << std::endl;
    return -1;
  }

  MobileBase robot(true);
  robot.Connect(device_name);

  while (true) {
    auto system_state = robot.GetSystemState();
    auto motion_state = robot.GetMotionState();
    auto odom = robot.GetOdometry();
    auto battery = robot.GetBatteryState();

    auto light_state = robot.GetLightState();
    auto ultrasonic_data = robot.GetUltrasonicData();
    auto tof_data = robot.GetTofData();

    robot.SetMotionCommand({{0.5, 0, 0}, {0, 0, 0.5}});

    std::cout << "Linear: " << ConvertToString(odom.linear.x) << ", ";
    std::cout << "Angular: " << ConvertToString(odom.angular.z) << " ; ";

    std::cout << "Position: (" << odom.position.x << "," << odom.position.y
              << "), ";
    std::cout << "Orientation: (" << ConvertToString(odom.orientation.x) << ","
              << ConvertToString(odom.orientation.y) << ","
              << ConvertToString(odom.orientation.z) << ","
              << ConvertToString(odom.orientation.w) << ") ; ";

    std::cout << "Ultrasonic: ";
    for (int i = 0; i < 7; ++i) {
      std::cout << "(" << i << ")"
                << ":" << std::setw(3) << ultrasonic_data[i].range << ", ";
    }
    printf("TOF1: %2f, TOF2: %2f; ", tof_data[0].range, tof_data[1].range);
    std::cout << " Battery : " << battery.voltage << std::endl;

    usleep(20000);
  }
}
