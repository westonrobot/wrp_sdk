#include <memory>
#include <thread>
#include <iostream>

#include "wrp_sdk/peripheral/imu_sensor_hipnuc.hpp"

using namespace westonrobot;

void ImuCallback(const ImuMsg &data) {
  std::cout << "Received Imu message: \n";
  // std::cout << "Timestamp: " << data.time_stamp << std::endl;
  std::cout << "Linear acceleration: \n";
  std::cout << "x: " << data.linear_acceleration.x
            << "\ny: " << data.linear_acceleration.y
            << "\nz: " << data.linear_acceleration.z << std::endl;
  std::cout << "---------------\n";
  std::cout << "Angular velocity: \n";
  std::cout << "x: " << data.angular_velocity.x
            << "\ny: " << data.angular_velocity.y
            << "\nz: " << data.angular_velocity.z << std::endl;
  std::cout << "---------------\n";
  std::cout << "Orientation: \n";
  std::cout << "x: " << data.orientation.x << "\ny: " << data.orientation.y
            << "\ny: " << data.orientation.z << "\nw: " << data.orientation.w
            << std::endl;
  std::cout << "===============\n\n";
}

int main(int argc, char **argv) {
  std::string device_path = "/dev/ttyUSB0";
  if (argc > 1) device_path = argv[1];
  std::unique_ptr<ImuInterface> imu = std::make_unique<ImuSensorHipnuc>();
  imu->SetDataReceivedCallback(ImuCallback);
  imu->Connect("can0");

  //  imu->Setup(device_path, 115200);
  //  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  while (imu->IsOkay()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  return 0;
}