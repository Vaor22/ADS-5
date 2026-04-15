// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int kSize>
class TStack {
 private:
  T arr[kSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == kSize - 1;
  }

  void push(const T& value) {
    if (!isFull()) {
      arr[++topIndex] = value;
    }
  }

  T pop() {
    if (!isEmpty()) {
      return arr[topIndex--];
    }
    return T();
  }

  T get() const {
    if (!isEmpty()) {
      return arr[topIndex];
    }
    return T();
  }
};

#endif  // INCLUDE_TSTACK_H_
