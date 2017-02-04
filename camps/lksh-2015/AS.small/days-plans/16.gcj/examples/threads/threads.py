import threading

def f(n):
  cnt = 0
  while True:
    #print(n, cnt)
    cnt += 1

threading.Thread(target=f, args=(1,)).start()
threading.Thread(target=f, args=(2,)).start()
threading.Thread(target=f, args=(3,)).start()
threading.Thread(target=f, args=(4,)).start()
