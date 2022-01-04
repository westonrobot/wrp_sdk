/*
 * sdk_demo.cpp
 *
 * Created on: Jun 14, 2021 13:59
 * Description:
 *
 * You can find header "wrp_sdk/mobile_base/westonrobot/mobile_base.hpp" in
 *  folder "/opt/weston_robot/include"
 *
 * Copyright (c) 2021 Weston Robot Pte. Ltd.
 */

#include <unistd.h>
#include <atomic>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "wrp_sdk/mobile_base/westonrobot/mobile_base.hpp"

using namespace westonrobot;

std::string ConvertToString(double value) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << value;
  return stream.str();
}

void ControlLostCallback(void) {
  // This function should be non-blocking and short
  std::cout << "SDK has lost control!" << std::endl;
}

int main(int argc, char** argv) {
  /* Process arguments */
  std::string device_name;
  if (argc == 2) {
    device_name = {argv[1]};
    std::cout << "Specified CAN: " << device_name << std::endl;
  } else {
    std::cout << "Usage: sdk_demo <interface>" << std::endl
              << "Example 1: ./sdk_demo can0" << std::endl;
    return -1;
  }

  /* Create a mobile base object and try to gain control token */
  std::shared_ptr<MobileBase> robot;
  robot = std::make_shared<MobileBase>();

  robot->RegisterLoseControlCallback(ControlLostCallback);

  robot->Connect(device_name);

  robot->RequestControl();

  MotionResetCommand motion_reset_command;
  motion_reset_command.type = MotionResetCommandType::kOdometry;
  robot->SetMotionResetCommand(motion_reset_command);

  LightCommand light_command;
  light_command.command.intensity = 20;
  light_command.command.mode = LightMode::kCustom;
  robot->SetLightCommand(light_command);

  // light_command.command.mode = LightMode::kEnquiry;
  // robot->SetLightCommand(light_command);

  auto light_state = robot->GetLightState();

  std::cout << "Light State: " << (int)light_state.state.mode << " "
            << light_state.state.intensity << std::endl;

  /* Now you can enter the main control loop*/
  while (true) {
    if (robot->SdkHasControlToken()) {
      robot->SetMotionCommand({{0, 0, 0}, {0, 0, 0}});
    } else {
      robot->RequestControl();
    }

    // get robot and sensor state
    auto system_state = robot->GetSystemState();
    auto motion_state = robot->GetMotionState();
    auto odom = robot->GetOdometry();
    auto battery = robot->GetBatteryState();

    // only when there is relevant sensor available
    auto ultrasonic_data = robot->GetUltrasonicData();
    auto tof_data = robot->GetTofData();
    auto rc_state = robot->GetRcState();

    std::cout << "Linear: " << ConvertToString(odom.linear.x) << ", ";
    std::cout << "Angular: " << ConvertToString(odom.angular.z) << " ; ";
    std::cout << "Position_x: " << ConvertToString(odom.position.x) << ", ";
    std::cout << "Position_y: " << ConvertToString(odom.position.y) << " ;\n";
    std::cout << "Orientation_x: " << ConvertToString(odom.orientation.x)
              << ", ";
    std::cout << "Orientation_y: " << ConvertToString(odom.orientation.y)
              << " ; ";
    std::cout << "Orientation_z: " << ConvertToString(odom.orientation.z)
              << ", ";
    std::cout << "Orientation_w: " << ConvertToString(odom.orientation.w)
              << " ; ";

    std::cout << "\nUltrasonic:\n";
    for (int i = 0; i < 8; ++i)
      std::cout << i << ":" << ultrasonic_data.data[i].range << std::endl;

    std::cout << "\nSystemState:\n";
    std::cout << "Rc_connected: " << system_state.rc_connected << std::endl;
    std::cout << "Error_code: " << (int)system_state.error_code << std::endl;
    std::cout << "Operational_state: " << (int)system_state.operational_state
              << std::endl;
    std::cout << "Control_state: " << (int)system_state.control_state
              << std::endl;

    std::cout << "Desired_linear: " << motion_state.desired_linear.x << " "
              << motion_state.desired_angular.z << " ; ";
    std::cout << " Collision_detected: " << motion_state.collision_detected
              << " ; "
              << "Assisted_mode: " << motion_state.assisted_mode_enabled
              << std::endl;

    std::cout << " Axes: " << rc_state.axes[0] << " " << rc_state.axes[1] << " "
              << rc_state.axes[2] << " " << rc_state.axes[3] << " ";
    std::cout << rc_state.axes[4] << " " << rc_state.axes[5] << " "
              << rc_state.axes[6] << " " << rc_state.axes[7] << std::endl;

    std::cout << " Buttons: " << rc_state.buttons[0] << " "
              << rc_state.buttons[1] << " " << rc_state.buttons[2] << " "
              << rc_state.buttons[3] << " ";
    std::cout << rc_state.buttons[4] << " " << rc_state.buttons[5] << " "
              << rc_state.buttons[6] << " " << rc_state.buttons[7] << std::endl;

    std::cout << " Battery : " << battery.voltage << std::endl;

    usleep(100000);
  }
  robot->RenounceControl();
}
