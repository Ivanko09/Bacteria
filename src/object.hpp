#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "field.hpp"

class Object {
 public:
  Object(Field &field, bool primary, bool collider);
  virtual ~Object() = 0;

  bool GetAlive() const;
  void SetAlive(bool value);

  bool IsPrimary() const;
  bool IsCollider() const;

  float GetX() const;
  float GetY() const;

  float GetRadius() const;

  virtual void Collision(std::shared_ptr<Object> with);
  virtual void Tick(float delta) = 0;

  void PlaceOnField();

 protected:
  void SetX(float value);
  void SetY(float value);
  void SetRadius(float value);

  void Move(float x, float y);

 private:
  bool alive_ = true;
  const bool primary_ = false;
  const bool collider_ = false;

  float radius_;
  float x_, y_;

  Field &field_;
};

#endif
