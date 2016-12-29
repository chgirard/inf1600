uint16_t clearFilterFrequency_;
uint16_t redFilterFrequency_;
uint16_t greenFilterFrequency_;
uint16_t blueFilterFrequency_;
uint16_t calibrationFrequency_;

void getColor() {
  if (clearFilterFrequency_ > calibrationFrequency_ * 0.8) {
    return white;
  }
  else {
    if (redFilterFrequency_ > blueFilterFrequency_ && redFilterFrequency_ > greenFilterFrequency_) {
      return red;
    }
    else {
      if (greenFilterFrequency_ > blueFilterFrequency_) {
        return green;
      }
      else {
        return blue;
      }
    }
  }
}
