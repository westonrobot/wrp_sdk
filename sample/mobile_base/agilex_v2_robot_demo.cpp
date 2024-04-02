/**
 * @file agilex_v2_robot_demo.cpp
 * @brief Agilex Robot Base V2 API usage demo
 * @date 02-04-2024
 *
 * Demo showing the Agilex robot bases running Agilex's V2 protocol API.
 *
 * @copyright Copyright (c) 2024 Weston Robot Pte. Ltd.
 */

#include <unistd.h>

#include <iomanip>
#include <sstream>
#include <iostream>

#include "wrp_sdk/mobile_base/agilex/agilex_base_v2_adapter.hpp"

using namespace westonrobot;

std::string ConvertToString(double value) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << value;
  return stream.str();
}

int main(int argc, char** argv) {
  std::string device_name;

  if (argc == 2) {
    device_name = {argv[1]};
    std::cout << "Specified CAN: " << device_name << std::endl;
  } else {
    std::cout << "Usage: sample_agilex_v2_robot_demo <interface>" << std::endl
              << "Example 1: ./sample_agilex_v2_robot_demo can0" << std::endl;
    return -1;
  }

  AgilexBaseV2Adapter robot;
  robot.Connect(device_name);

  //ATTN: handshake_demo for possible error codes
  if (robot.RequestControl(500) != HandshakeReturnCode::kControlAcquired) {
    std::cout << "Failed to gain control" << std::endl;
    return -1;
  }

  uint8_t count = 0;
  while (true) {
    auto system_state = robot.GetSystemState();
    auto motion_state = robot.GetMotionState();
    auto odom = robot.GetOdometry();
    auto battery = robot.GetBatteryState();

    auto ultrasonic_data = robot.GetUltrasonicData();
    auto tof_data = robot.GetTofData();
    auto rc_state = robot.GetRcState();

    if (robot.SdkHasControlToken())
      robot.SetMotionCommand({{0, 0, 0}, {0, 0, 0}});

    // set light command and query
    LightCommand light_command;
    light_command.id = 0;
    if (++count >= 100) {
      MotionResetCommand motion_reset_command;
      motion_reset_command.type = MotionResetCommandType::kOdometry;
      robot.SetMotionResetCommand(motion_reset_command);
      count = 0;
    } else if (++count >= 10) {
      light_command.command.mode = LightMode::kEnquiry;
      robot.SetLightCommand(light_command);
    } else if (++count >= 5) {
      light_command.command.intensity = 20;
      light_command.command.mode = LightMode::kCustom;
      robot.SetLightCommand(light_command);
    }

    auto light_state = robot.GetLightState();
    std::cout << "Light State: " << (int)light_state.state.mode << " "
              << light_state.state.intensity << std::endl;

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
      std::cout << i << ":" << ultrasonic_data[i].range << std::endl;

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
    std::cout << " Battery : " << battery.voltage << std::endl;

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
  robot.RenounceControl(500);
}
