/*
 * handshake_demo.cpp
 *
 * Created on: Mar 10, 2021 10:35
 * Description:
 *
 * Copyright (c) 2021 Weston Robot Pte. Ltd.
 */

#include <unistd.h>
#include <iostream>

#include "wrp_sdk/mobile_base/westonrobot/mobile_base.hpp"

using namespace westonrobot;

int main(int argc, char **argv) {
  std::string device_name;

  if (argc == 2) {
    device_name = {argv[1]};
    std::cout << "Specified CAN: " << device_name << std::endl;
  } else {
    std::cout << "Usage: handshake_demo <interface>" << std::endl
              << "Example 1: ./handshake_demo can0" << std::endl;
    return -1;
  }

  MobileBase robot;
  robot.Connect(device_name);

  std::string line;
  while (true) {
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << "----Please input a char for the subsequent process----"
              << std::endl;
    std::cout << "r: "
              << "request control\t"
              << "d: "
              << "renounce control\t" << std::endl;
    std::cout << "s: "
              << "speed control\t"
              << "l: "
              << "light control\t" << std::endl;
    std::cin >> line;

    if (line == "r") {
      auto feedback = robot.RequestControl(500);
      switch (feedback) {
        case HandshakeReturnCode::kRobotBaseNotAlive:
          std::cout << "RobotBaseNotAlive" << std::endl;
          break;
        case HandshakeReturnCode::kControlAcquired:
          std::cout << "ControlAcquired" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RobotBaseFault:
          std::cout << "ControlRejected_RobotBaseFault" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RcHaltTriggered:
          std::cout << "ControlRejected_RcHaltTriggered" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RcControlActive:
          std::cout << "ControlRejected_RcControlActive" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_TokenTransferInterrupted:
          std::cout << "ControlRejected_TokenTransferInterrupted" << std::endl;
          break;
        case HandshakeReturnCode::kControlRequestTimeout:
          std::cout << "ControlRequestTimeout" << std::endl;
          break;
      }
    } else if (line == "d") {
      auto feedback = robot.RenounceControl(500);
      switch (feedback) {
        case HandshakeReturnCode::kControlHandedOver:
          std::cout << "ControlHandedOver" << std::endl;
          break;
        case HandshakeReturnCode::kRenounceRequestTimeout:
          std::cout << "RenounceRequestTimeout" << std::endl;
          break;
      }
    }
    usleep(100000);
  }
  return 0;
}
