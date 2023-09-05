#include <cstdlib>
#include <cstring>
class N {
public:
  int _number;
  char _annotation[108];
  N(int n) : _number(n) {}
  void setAnnotation(const char *str) { memcpy(_annotation, str, strlen(str)); }
  int operator+(const N &rhs) const { return _number + rhs._number; }
};

int main(int argc, char *argv[]) {
  if (argc < 2)
    exit(1);
  N *a = new N(5);
  N *b = new N(6);
  a->setAnnotation(argv[1]);
  return *a + *b;
}
