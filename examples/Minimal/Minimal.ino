#include <Arduino.h>
#include <SuperJupiterTimeAggregate.h>
using namespace superjupiter::time_aggregate;
void setup() {
  Serial.begin(115200);
  TimeAggregate minutes(60000);
  minutes.push(20, 0);
  minutes.push(21, 1000);
  minutes.push(22, 60000);
  Summary previous;
  minutes.takeCompleted(previous);
  Serial.println("SuperJupiter TimeAggregate example ran. Hardware validation pending.");
}
void loop() {}
