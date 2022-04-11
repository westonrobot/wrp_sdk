/*
 * test_power_regulator_v2.cpp
 *
 * Created 3/25/22 2:15 PM
 * Description:
 *
 * Copyright (c) 2022 Weston Robot Pte. Ltd.
 */

#include <unistd.h>

#include <thread>
#include <chrono>
#include <iostream>

#include "wrp_sdk/peripheral/power_regulator_v2.hpp"

using namespace westonrobot;

void PowerRegulatorStateCallback(
    const PowerRegulatorInterface::DeviceState &state) {
  std::cout << "Input voltage: " << state.input_voltage
            << ", temperature: " << state.temperature
            << ", fan-speed: " << state.fan_speed << std::endl;
  std::cout << "[19V]: " << std::boolalpha
            << state.channels.at(PowerRegulatorV2::kChannel19V).enabled
            << std::hex << ", voltage: "
            << state.channels.at(PowerRegulatorV2::kChannel19V).voltage
            << ", current: "
            << state.channels.at(PowerRegulatorV2::kChannel19V).current
            << std::endl;
  std::cout << "[12V]: " << std::boolalpha
            << state.channels.at(PowerRegulatorV2::kChannel12V).enabled
            << std::hex << ", voltage: "
            << state.channels.at(PowerRegulatorV2::kChannel12V).voltage
            << ", current: "
            << state.channels.at(PowerRegulatorV2::kChannel12V).current
            << std::endl;
  std::cout << "[12Vi]: " << std::boolalpha
            << state.channels.at(PowerRegulatorV2::kChannel12Vi).enabled
            << std::hex << ", voltage: "
            << state.channels.at(PowerRegulatorV2::kChannel12Vi).voltage
            << ", current: "
            << state.channels.at(PowerRegulatorV2::kChannel12Vi).current
            << std::endl;
  std::cout << "[5Vi]: " << std::boolalpha
            << state.channels.at(PowerRegulatorV2::kChannel5Vi).enabled
            << std::hex << ", voltage: "
            << state.channels.at(PowerRegulatorV2::kChannel5Vi).voltage
            << ", current: "
            << state.channels.at(PowerRegulatorV2::kChannel5Vi).current
            << std::endl;

  std::cout << "---------------" << std::endl;
}

int main(int argc, char *argv[]) {
  std::string device_path = "can0";
  if (argc > 1) device_path = argv[1];

  std::unique_ptr<PowerRegulatorInterface> regulator =
      std::make_unique<PowerRegulatorV2>();
  regulator->SetDataReceivedCallback(PowerRegulatorStateCallback);
  regulator->Connect(device_path);

  // start 19V channel first
  regulator->SetChannelState(PowerRegulatorV2::kChannel19V, true);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // start 12V channel after 2s
  regulator->SetChannelState(PowerRegulatorV2::kChannel12V, true);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // start 12V isolated channel after another 2s
  regulator->SetChannelState(PowerRegulatorV2::kChannel12Vi, true);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // start 5V isolated channel after another 2s
  regulator->SetChannelState(PowerRegulatorV2::kChannel5Vi, true);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  bool toggle_flag = true;
  while (regulator->IsOkay()) {
    // do other work, while listening to state feedback via callback
    sleep(5);
  }

  return 0;
}