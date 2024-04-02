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
  std::unique_ptr<UltrasonicInterface>
      ultrasonic = std::make_unique<UltrasonicSensorDyp>();
  ultrasonic->SetDataReceivedCallback(UltrasonicCallback);
  ultrasonic->Connect(device_path, 9600);

  while (ultrasonic->IsOkay()) {
    sleep(1);
  }
  return 0;
}