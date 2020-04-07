#include <iostream>
#include <iomanip>
#include <bitset>
#include <stdlib.h> 
#include <chrono>
#include <ctime>
#include <time.h>
using namespace std;

typedef unsigned __int128 i128;

i128 ONE = 1;
i128 THREE = 3;
i128 SEVEN = 7;

struct ipair {
  i128 n1;
  i128 n2;
};

#include <stdio.h>
#include <inttypes.h>

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19
#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)


static int printdec(i128 u128)
{
    int rc;
    if (u128 > UINT64_MAX)
    {
        i128 leading  = u128 / P10_UINT64;
        uint64_t  trailing = u128 % P10_UINT64;
        rc = printdec(leading);
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc;
}

void printhex(i128 x) {
  cout << internal << setfill('0');

  uint64_t high = (uint64_t)(x >> 64);
  cout << hex << setw(16) << high;

  uint64_t low = (uint64_t)x;
  cout << hex << setw(16) << low << endl;
}

void printbin(i128 x) {
  cout << internal << setfill('0');

  uint64_t high = (uint64_t)(x >> 64);
  cout << std::bitset<64>(high);

  uint64_t low = (uint64_t)x;
  cout << std::bitset<64>(low) << endl;
}



i128 FIB [128] = { };

void seedFib() {
  FIB[0] = 1;
  FIB[1] = 2;
  for (int i = 2; i <= 127; i ++) {
    FIB[i] = FIB[i-1] + FIB[i-2];
  }
}

i128 genInput() {
  srand(time(NULL));
  i128 res = ONE << 1;

  int i = 0;
  while (i <= 123) {
    if (rand() % 3) {
       res = res << 1;
       i += 1;
    } else {
      res = res << 1;
      res += ONE;
      res = res << 1;
      i += 2;
    }
  }

  return res;
}

i128 bitAdd(i128 x, i128 y) {
  bool c = 0;
  i128 res = 0;
  i128 a, b, r;
  for (int i = 0; i <= 127; i ++) {
    a = (x >> i) & ONE;
    b = (y >> i) & ONE;
    r = a + b + c;
    c = (r > 1);
    if (r & ONE) {
      res += (ONE << i);
    }
  }
  return res;
}

i128 encode(i128 n) {
  int i = 127;
  i128 res = 0;

  for (i; i >= 0; i --) {
    if (n >= FIB[i]) {
      n -= FIB[i];
      res += (ONE << i);
      //res = bitAdd(res, ONE << i);
    }
  }
  return res;
}

i128 decode(i128 n) {
  int i = 0;
  i128 res = 0;

  for (i; i <= 127; i ++) {
    if (n & (ONE << i)) {
      res += FIB[i];
      //res = bitAdd(res, FIB[i]);
    }
  }
  return res;
}


ipair addOne(ipair p, int ind) {
  if (p.n1 & (ONE << ind)) {
    p.n2 = p.n2 | (ONE << ind);
  }
  p.n1 = p.n1 ^ (ONE << ind);

  return p;
}

ipair addFib(i128 F1, i128 F2) {
  ipair p;
  p.n1 = F1 ^ F2;
  p.n2 = F1 & F2;
  return p;
}

ipair deTwo(ipair p) {
  int ind = 127;

  while (ind >= 0) {

//    cout << "ind = " << ind << endl;
//    cout << "n2 = ";
//    printbin(p.n2);
//    cout << "n1 = ";
//    printbin(p.n1);
//    cout << endl;

    if (!(p.n2 & (ONE << ind))) {
      ind -= 1;
      continue;
    }

    p = addOne(p, ind + 1);

    p.n2 = p.n2 ^ (ONE << ind);

    if (ind == 0) {
      break;
    } else if (ind == 1) {
      p = addOne(p, ind - 1);
      ind -= 1;
      continue;
    } else if (ind == 2) {
      p = addOne(p, ind - 2);
      ind -= 1;
      continue;
    }

    if (p.n2 & (ONE << (ind - 2))) {
      p = addOne(p, ind - 2);
    } else if (p.n1 & (ONE << (ind - 2))) {
      if (p.n1 & (ONE << (ind - 3))) {
        p = addOne(p, ind - 1);
        p.n1 = p.n1 ^ (ONE << (ind - 3));
      } else {
        p = addOne(p, ind - 2);
      }
    } else {
      if (p.n2 & (ONE << (ind - 3))) {
        p = addOne(p, ind - 1);
        p.n2 = p.n2 ^ (ONE << (ind - 3));
        p.n1 = p.n1 ^ (ONE << (ind - 3));
      } else {
        p = addOne(p, ind - 2);
      }
    }

    ind -= 1;
  }
  return p;
}

i128 deCont(i128 n) {
  int ind = 127;

  while (ind >= 1) {

    if (((n >> (ind - 1)) & THREE) == 3) {
      n = n ^ (SEVEN << (ind - 1));
    }
    ind -= 1;
  }

  ind = 0;

  while (ind <= 125) {

    if (((n >> ind) & THREE) == 3) {
      n = n ^ (SEVEN << (ind));
    }
    ind += 1;
  }

  return n;
}

int main() {
  seedFib();

  i128 x = genInput();
  i128 y = genInput();
//  printbin(x);
//  printdec(decode(x));
//  printf("\n");
//  printbin(y);
//  printdec(decode(y));
//  printf("\n");
//  printdec(decode(x) + decode(y));
//  printf("\n");

  auto t_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 10000; i ++) {
    ipair p = addFib(x, y);
    p = deTwo(p);
    i128 z = deCont(p.n1);
  }

  auto t_end = std::chrono::high_resolution_clock::now();
  std::cout << std::fixed << std::setprecision(5) << "Wall clock time passed: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";

  t_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 10000; i ++) {
    i128 xe = decode(x);
    i128 ye = decode(y);
    i128 ze = encode(xe + ye);
    //i128 ze = encode(bitAdd(xe, ye));
  }

  t_end = std::chrono::high_resolution_clock::now();
  std::cout << std::fixed << std::setprecision(5) << "Wall clock time passed: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";

  return 0;
}
