/*
 * test_gps_receiver.cpp
 *
 * Created on: Jun 27, 2021 20:35
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include <unistd.h>
#include <iostream>

#include "wrp_sdk/peripheral/gps_receiver_nmea.hpp"

using namespace westonrobot;

int main(int argc, char **argv) {
  std::string device_path = "/dev/ttyUSB0";
  if (argc > 1) device_path = argv[1];
  std::unique_ptr<GpsReceiverNmea> gps = std::make_unique<GpsReceiverNmea>();
  gps->Connect(device_path, 115200);
  // gps->ResetFilter(false);
  // gps->SetFilter(NmeaParser::RMC_MASK);

  while (gps->IsOkay()) {
    auto data = gps->GetLastData();
    if (data.status.status == NavSatStatusMsg::STATUS_NO_FIX) {
      std::cout << "No fix" << std::endl;
    } else if (data.status.status == NavSatStatusMsg::STATUS_GBAS_FIX) {
      std::cout << "RTK Fixed/Float (" << static_cast<int>(data.status.status)
                << "," << data.status.service << "), (lat, lon, alt): ("
                << data.latitude << "," << data.longitude << ","
                << data.altitude << ")" << std::endl;
    } else if (data.status.status == NavSatStatusMsg::STATUS_FIX) {
      std::cout << "Fixed (" << static_cast<int>(data.status.status) << ","
                << data.status.service << "), (lat, lon, alt): ("
                << data.latitude << "," << data.longitude << ","
                << data.altitude << ")" << std::endl;
    } else if (data.status.status == NavSatStatusMsg::STATUS_SBAS_FIX) {
      std::cout << "Differential GNSS (" << static_cast<int>(data.status.status)
                << "," << data.status.service << "), (lat, lon, alt): ("
                << data.latitude << "," << data.longitude << ","
                << data.altitude << ")" << std::endl;
    }
    usleep(100000);
  }

  return 0;
}
