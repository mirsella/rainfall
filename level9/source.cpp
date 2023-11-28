#include <cstdlib>
#include <cstring>
// size of 108 bytes
class N {
public:
  // points to N::operator+
  int (N::*add)(const N &rhs); // is at base + 0, takes 4 bytes
  char annotation[100]; // is at base + 4, takes 100 bytes
  int number; // is at base + 104, takes 4 bytes
  N(int n) : number(n), add(&N::operator+){}
  void setAnnotation(const char *str) { memcpy(annotation, str, strlen(str)); }
  int operator+(const N &rhs) { return number + rhs.number; }
};

int main(int argc, char *argv[]) {
  if (argc < 2)
    exit(1);
  N *a = new N(5);
  N *b = new N(6);
  a->setAnnotation(argv[1]);
  b->add(a);
  // originaly:
  /* return (**b)(a, b); */
}
