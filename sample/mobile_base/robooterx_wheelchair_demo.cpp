/**
 * @file robooterx_wheelchair_demo.cpp
 * @brief Robooterx Wheelchair API usage demo
 * @date 03-05-2024
 *
 * Demo showing the Robooterx Wheelchair running Robooterx's protocol API.
 *
 * @copyright Copyright (c) 2024 Weston Robot Pte. Ltd.
 */

#include <unistd.h>

#include <iomanip>
#include <sstream>
#include <iostream>

#include "wrp_sdk/mobile_base/bangbang/robooterx_base_adapter.hpp"

int main(int argc, char const *argv[]) {
  std::string device_name;

  if (argc == 2) {
    device_name = {argv[1]};
    std::cout << "Specified CAN: " << device_name << std::endl;
  } else {
    std::cout << "Usage: sample_robooterx_wheelchair_demo <interface>"
              << std::endl
              << "Example 1: ./sample_robooterx_wheelchair_demo can0"
              << std::endl;
    return -1;
  }

  westonrobot::RobooterXBaseAdapter base;
  base.Connect(device_name);

  if (base.RequestControl(500) !=
      westonrobot::HandshakeReturnCode::kControlAcquired) {
    std::cout << "Failed to gain control" << std::endl;
    return -1;
  }

  while (true) {
    std::cout << "Checking robot base status..." << std::endl;
    if (base.IsRobotBaseAlive()) {
      std::cout << "Robot base is alive." << std::endl;
    } else {
      std::cout << "Robot base is not alive." << std::endl;
    }

    if (base.SdkHasControlToken()) {
      std::cout << "Control is acquired." << std::endl;
    } else {
      std::cout << "Control is not acquired." << std::endl;
    }

    westonrobot::RcState rc_state = base.GetRcState();
    std::cout << "RC channel state: " << std::endl;
    std::cout << "  Axis 1 (Horizontal): " << rc_state.axes[0] << std::endl;
    std::cout << "  Axis 2 (Vertical):" << rc_state.axes[1] << std::endl;
    std::cout << "  Button 1 (Newbie mode): " << rc_state.buttons[0]
              << std::endl;

    westonrobot::MotionState motion_state = base.GetMotionState();
    std::cout << "Beginner mode enabled: " << motion_state.assisted_mode_enabled
              << std::endl;

    westonrobot::Odometry odom = base.GetOdometry();
    std::cout << "Odometry: " << std::endl;
    std::cout << "  Linear X: " << odom.linear.x << " m/s" << std::endl;
    std::cout << "  Angular Z: " << odom.angular.z << " rad/s" << std::endl;

    westonrobot::SystemState system_state = base.GetSystemState();
    std::cout << "Base state: " << std::endl;
    std::cout << "  Operational State: "
              << static_cast<int>(system_state.operational_state) << std::endl;
    std::cout << "  Control State: "
              << static_cast<int>(system_state.control_state) << std::endl;

    westonrobot::BatteryState bms_data = base.GetBatteryState();
    westonrobot::BatteryState bms_data2 = base.GetSecondaryBatteryState();
    std::cout << "Primary BMS: " << std::endl;
    std::cout << "  SOC: " << bms_data.percentage << "%" << std::endl;
    std::cout << "Secondary BMS: " << std::endl;
    std::cout << "  SOC: " << bms_data2.percentage << "%" << std::endl;
    std::cout << "  voltage: " << bms_data2.voltage << "V" << std::endl;

    std::cout << "Controlling robot base..." << std::endl;

    static int mode = 1;
    base.SetMotionMode(static_cast<westonrobot::MotionMode>(mode++));
    if (mode > 5) {
      mode = 1;
    }

    westonrobot::MotionCommand cmd;
    cmd.linear.x = 0.5;
    cmd.angular.z = 0.0;
    // base.SetMotionCommand(cmd);
    
    std::cout << "=========================================" << std::endl;

    usleep(100000);
  }

  base.RenounceControl(500);

  return 0;
}
