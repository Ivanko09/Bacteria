#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "bacterium.hpp"
#include "field.hpp"
#include "food.hpp"

class Simulation {
 public:
  Simulation();

  void PushBactery(const Bacterium& bacterium);
  void PushFood(const Food& bacterium);

  void Run(float delta_time);
  void InitRandomly();

  const Field& GetField() const;

 private:
  float from_last_food_spawn_ = 0;
  Field field_;
  std::vector<std::shared_ptr<Bacterium>> dead_;
};

#endif
