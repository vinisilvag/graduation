// Copyright 2018 Universidade Federal de Minas Gerais (UFMG)

#include "complexo.h"

#include <cmath>

Complexo::Complexo() : Complexo(0, 0) {
}

Complexo::Complexo(double a) : Complexo(a, 0) {
}

Complexo::Complexo(double a, double b) {
  real_ = a;
  imaginario_ = b;
}

double Complexo::real() const {
  return real_;
}

double Complexo::imag() const {
  return imaginario_;
}

bool Complexo::operator==(Complexo x) const {
  return (x.real_ == real_) && (x.imaginario_ == imaginario_);
}

void Complexo::operator=(Complexo x) {
  real_ = x.real_;
  imaginario_ = x.imaginario_;
} 

double Complexo::modulo() const {
  return sqrt(pow(real_, 2) + pow(imaginario_, 2));
}

Complexo Complexo::conjugado() const {
  Complexo c;
  
  c.real_ = real_;
  c.imaginario_ = -imaginario_;

  return c;
}

Complexo Complexo::operator-() const {
  Complexo c;

  c.real_ = -real_;
  c.imaginario_ = -imaginario_;

  return c;
}

Complexo Complexo::inverso() const {
  Complexo i;

  i.real_ = real_/(pow(real_, 2) + pow(imaginario_, 2));
  i.imaginario_ = -imaginario_/(pow(real_, 2) + pow(imaginario_, 2));

  return i;
}

Complexo Complexo::operator+(Complexo y) const {
  Complexo s(real_ + y.real_, imaginario_ + y.imaginario_);

  return s;
}

Complexo Complexo::operator-(Complexo y) const {
  Complexo s(real_ - y.real_, imaginario_ - y.imaginario_);

  return s;
}

Complexo Complexo::operator*(Complexo y) const {
  Complexo p(real_ * y.real_ - (imaginario_ * y.imaginario_), real_ * y.imaginario_ + imaginario_ * y.real_);

  return p;
}

Complexo Complexo::operator/(Complexo y) const {
  Complexo r;

  double den = pow(y.real_, 2) + pow(y.imaginario_, 2);

  r.real_ = (real_ * y.real_ + imaginario_ * y.imaginario_)/den;
  r.imaginario_ = (imaginario_ * y.real_ - real_ * y.imaginario_)/den;

  return r;
}
