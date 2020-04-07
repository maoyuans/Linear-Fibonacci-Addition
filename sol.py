from random import *

fib = [1, 2]

def main():
  #a = randint(100000, 1000000)
  #b = randint(100000, 1000000)
  #print(a, b)
  #A = fibEnc(a)
  #B = fibEnc(b)
  #print(ts(A))
  #print(ts(B))
  #print(fibDec(A),fibDec(B))
  #C = lstAdd(A, B)
  #print(ts(C))
  #print(fibDec(C))
  #D = deTwo(C)
  #print(ts(D))
  #print(fibDec(D))
  #E = deCont(D)
  #print(ts(E))
  #print(fibDec(E))
  it = 1000000

  for i in range(it):
    if (i % 10000 == 0):
      print('Testing '+str(i)+'/'+str(it)+'...')
    err = False

    a = randint(10000000000, 1000000000000)
    b = randint(10000000000, 1000000000000)
    A = fibEnc(a)
    B = fibEnc(b)
    if (fibDec(A) != a):
      print("Error 1... "+str(a))
      continue
    if (fibDec(B) != b):
      print("Error 2... "+str(b))
      continue
    C = lstAdd(A, B)
    c = fibDec(C)
    if (c != a + b):
      print("Error 3... "+str(a)+' '+str(b))
      continue
    D = deTwo(C)
    if (fibDec(D) != c):
      print("Error 4... "+str(a)+' '+str(b))
      continue
    for n in D:
      if (n >= 2):
        print("Error 5... "+str(a)+' '+str(b))
        err = True
        break
    if (err):
      continue
    E = deCont(D)
    if (fibDec(E) != c):
      print("Error 6... "+str(a)+' '+str(b))
      continue
    for n in range(len(E)-1):
      if (E[n] == 1 and E[n+1] == 1):
        print("Error 7... "+str(a)+' '+str(b))
        err = True
        break
    if (err):
      continue

def fibEnc(n):
  global fib

  while (fib[-1] < n):
    fib.append(fib[-1] + fib[-2])

  res = []
  ind = len(fib) - 1

  while (fib[ind] > n):
    ind -= 1
  res = (ind + 1) * [0]
  res[ind] = 1
  n -= fib[ind]

  while (n > 0):
    while (fib[ind] > n):
      ind -= 1
    res[ind] = 1
    n -= fib[ind]

  return res


def fibDec(lst):
  global fib

  while (len(fib) < len(lst)):
    fib.append(fib[-1] + fib[-2])

  res = 0
  for i in range(len(lst)):
    res += fib[i] * lst[i]

  return res


def lstAdd(lst1, lst2):
  ind = 0
  res = []

  while (ind < len(lst1) and ind < len(lst2)):
    res.append(lst1[ind] + lst2[ind])
    ind += 1

  if (ind == len(lst1)):
    res += lst2[ind:]
  else:
    res += lst1[ind:]

  return res


def deTwo(lst):
  ind = len(lst) - 1

  while (ind >= 0):
    if (lst[ind] < 2):
      ind -= 1
      continue

    if (ind + 1 >= len(lst)):
      lst.append(1)
    else:
      lst[ind+1] += 1

    lst[ind] -= 2

    if (ind == 2):
      lst[ind-2] += 1
      ind -= 1
      continue
    elif (ind == 1):
      lst[ind-1] += 1
      ind -= 1
      continue
    elif (ind == 0):
      break

    if (lst[ind-2] == 0):
      if (lst[ind-3] < 2):
        lst[ind-2] += 1
      else:
        lst[ind-1] += 1
        lst[ind-3] -= 1
    elif (lst[ind-2] == 1):
      if (lst[ind-3] == 0):
        lst[ind-2] += 1
      else:
        lst[ind-1] += 1
        lst[ind-3] -= 1
    else:
      lst[ind-2] += 1

    ind -= 1

  return lst

def deCont(lst):
  ind = len(lst) - 1

  while (ind >= 0):
    if (lst[ind] == 1):
      if (ind != 0 and lst[ind-1] == 1):
        lst[ind-1] -= 1
        lst[ind] -= 1
        if (ind + 1 >= len(lst)):
          lst.append(1)
        else:
          lst[ind+1] += 1
    ind -= 1

  ind = 0

  while (ind < len(lst)):
    if (lst[ind] == 1):
      if (ind != len(lst)-1 and lst[ind+1] == 1):
        lst[ind] -= 1
        lst[ind+1] -= 1
        if (ind + 2 >= len(lst)):
          lst.append(1)
        else:
          lst[ind+2] += 1
    ind += 1

  return lst


def ts(lst):
  res = ''
  for n in lst:
    res += str(n)
  return res

main()
