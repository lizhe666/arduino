#include "Arduino.h"

class VOC_MS1100_P211 {

private:
  int port;
  
public:
  VOC_MS1100_P211(int p); 
  ~VOC_MS1100_P211(); 
  float read(bool debug);
};