static int count = 0;

class Foo {
public:
#ifdef PURE_VIRTUAL
  virtual void alpha() = 0;
#else
  virtual void alpha() {
    count++;
  }
#endif
  
  virtual void beta() {
    count++;
  }
  
  Foo() {
    beta();
  }
};

class Bar:Foo {
public:
  virtual void alpha() {
  }
};

int main(int argc, char* argv[]) {
    Bar bar;

    return count;
}
