#ifndef ENUMS_H
#define ENUMS_H

namespace State
{
enum state {
  STEADY,
  DRYING
};

String toString(state s) {
  switch (s) {
    case STEADY:
      return "STEADY";
      break;
    case DRYING:
      return "DRYING";
      break;
  }
}
}

namespace Compressor
{
enum state {
  CHARGING,
  FULL
};
}


#endif
