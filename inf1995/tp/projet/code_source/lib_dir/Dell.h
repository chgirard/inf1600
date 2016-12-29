#ifndef DELL_H
#define DELL_H

  #include "Settings.h"

  namespace Dell {
    // The different to set the Dell
    enum Color {
        OFF, GREEN, RED
    };
  }

  // Sets the Dell to the requirered color
  void setLight(Dell::Color color);

#endif // !DELL_H
