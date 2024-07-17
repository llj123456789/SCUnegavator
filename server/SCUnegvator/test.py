import threading

a=list()
def ppp():
    while True:
        pass
a.append(threading.Thread(target=ppp))
a[len(a)-1].start()
print(type(a[0]))