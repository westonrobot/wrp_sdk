/**
 * @file handshake_demo.cpp
 * @brief Demonstrate the usage of the Handshake API
 * @date 02-04-2024
 *
 * Demo showing all possible codes returned by the control Handshake API for
 * robots.
 *
 * @copyright Copyright (c) 2024 Weston Robot Pte. Ltd.
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
    std::cin >> line;

    if (line == "r") {
      auto feedback = robot.RequestControl(500);
      switch (feedback) {
        case HandshakeReturnCode::kRobotBaseNotAlive:
          std::cout << "Robot Base Not Alive" << std::endl;
          break;
        case HandshakeReturnCode::kAlreadyGainedControl:
          std::cout << "Control Already Acquired" << std::endl;
          break;
        case HandshakeReturnCode::kControlAcquired:
          std::cout << "Control Acquired" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RobotBaseFault:
          std::cout << "Request Rejected, Robot Has Fault" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RcHaltTriggered:
          std::cout << "Request Rejected, RC Emergency Halt Active"
                    << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_RcControlActive:
          std::cout << "Request Rejected, RC Is In Control" << std::endl;
          break;
        case HandshakeReturnCode::kControlRejected_TokenTransferInterrupted:
          std::cout << "Request Interrupted" << std::endl;
          break;
        case HandshakeReturnCode::kControlRequestTimeout:
          std::cout << "Request Timed Out" << std::endl;
          break;
        default:
          break;
      }
    } else if (line == "d") {
      auto feedback = robot.RenounceControl(500);
      switch (feedback) {
        case HandshakeReturnCode::kControlHandedOver:
          std::cout << "Control Renounced" << std::endl;
          break;
        case HandshakeReturnCode::kRenounceRequestTimeout:
          std::cout << "Request Timed Out" << std::endl;
          break;
        case HandshakeReturnCode::kAlreadyLostControl:
          std::cout << "Control Already Renounced" << std::endl;
          break;
        default:
          break;
      }
    }
    usleep(100000);
  }
  return 0;
}
