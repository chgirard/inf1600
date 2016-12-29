#ifndef PRESCALER_H
#define PRESCALER_H

namespace lib {
  /**
   * @brief Differentes valeurs possible du prescaler
   */
  enum Prescaler {
      Prescaler_1 = 1, Prescaler_8 = 2, Prescaler_64 = 3, Prescaler_256 = 4,
      Prescaler_1024 = 5
  };
}
#endif // !PRESCALER_H
