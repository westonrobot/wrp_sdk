/**
 * @file ultrasonic_sensor_demo.cpp
 * @brief Ultrasonic Sensor API usage demo
 * @date 02-04-2024
 *
 * @copyright Copyright (c) 2024 Weston Robot Pte. Ltd.
 */
#include <unistd.h>

#include <memory>
#include <iostream>

#include "wrp_sdk/peripheral/ultrasonic_sensor_dyp.hpp"

using namespace westonrobot;

void UltrasonicCallback(const UltrasonicMsg &msg) {
  std::cout << "Range: ";
  for (const auto &dp : msg) {
    std::cout << dp.range << " ";
  }
  std::cout << std::endl;
  std::cout << "===============\n\n";
};

int main(int argc, char **argv) {
  std::string device_path = "/dev/ttyUSB0";
  if (argc > 1) device_path = argv[1];
  UltrasonicSensorDyp ultrasonic;
  ultrasonic.SetDataReceivedCallback(UltrasonicCallback);
  ultrasonic.Connect(device_path, 9600);

  while (ultrasonic.IsOkay()) {
    sleep(1);
  }
  return 0;
}