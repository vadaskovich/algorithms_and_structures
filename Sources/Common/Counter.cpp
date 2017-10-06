//
//  Counter.cpp
//  Common
//
//  Created by Bro on 10/5/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <chrono>
using namespace std::chrono;

#include "Counter.hpp"

Counter::Counter() {
  tick();
}

Timestamp GetTimestamp() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Timestamp Counter::millisecondsElapsed() {
  Timestamp current_timestamp = GetTimestamp();
  Timestamp result = current_timestamp - m_last_tick;
  m_last_tick = current_timestamp;
  return result;
}

float Counter::secondsElapsed() {
  Timestamp milliseconds = millisecondsElapsed();
  return milliseconds / 1000.0f;
}

void Counter::tick() {
  m_last_tick = GetTimestamp();
}

