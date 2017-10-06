//
//  Counter.hpp
//  Common
//
//  Created by Bro on 10/5/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef Counter_hpp
#define Counter_hpp

typedef long long Timestamp;

Timestamp GetTimestamp();

class Counter {
public:
  Counter();
  Timestamp millisecondsElapsed();
  float secondsElapsed();
  void tick();
  
private:
  Timestamp m_last_tick;
};


#endif /* Counter_hpp */
