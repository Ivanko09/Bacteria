#include "simulation.hpp"

const float radius = 10;

Simulation::Simulation() {}

void Simulation::PushBactery(const Bacterium &bacterium) {
  std::shared_ptr<Bacterium> b(new Bacterium(bacterium));
  field_.GetBacterium().push_back(b);
}

void Simulation::PushFood(const Food &bacterium) {
  std::shared_ptr<Food> b(new Food(bacterium));
  field_.GetEats().push_back(b);
}

void Simulation::Run(float delta_time) {
  for (auto &bactery : field_.GetBacterium()) bactery->Play(delta_time);
  auto it =
      std::remove_if(field_.GetBacterium().begin(), field_.GetBacterium().end(),
                     [](auto b) { return b->GetEnergy() <= 0; });

  for (auto i = it; i != field_.GetBacterium().end(); ++i) dead_.push_back(*it);
  field_.GetBacterium().erase(it, field_.GetBacterium().end());

  for (auto b : field_.GetBacterium()) {
    for (auto e : field_.GetEats()) {
      if (abs(b->GetX() - e->GetX()) < radius &&
          abs(b->GetY() - e->GetY()) < radius) {
        e->SetAlive(false);
        b->PushEnergy(100);
      }
    }
  }

  auto ite = std::remove_if(field_.GetEats().begin(), field_.GetEats().end(),
                            [](auto b) { return b->GetAlive() == false; });
  field_.GetEats().erase(ite, field_.GetEats().end());

  from_last_food_spawn_ += delta_time;

  if (from_last_food_spawn_ > 2) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
    from_last_food_spawn_ = 0;
  }
}

void Simulation::InitRandomly() {
  for (size_t i = 0; i < 100; i++) {
    auto b = Bacterium(GetField());
    b.PlaceRandomly();
    PushBactery(b);
  }
  for (size_t i = 0; i < 100; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }
}

const Field &Simulation::GetField() const { return field_; }
