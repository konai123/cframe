
import socket
import time
import random

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("127.0.0.1", 10050))

#Bias: 1, Offset: 4, LengthFieldSize: 4
bytes = b"OFFS\x04\x00\x00\x00AAAAA"

while(True):
    idx = random.randint(1, len(bytes)-1)
    sock.send(bytes[:idx])
    time.sleep(1);
    sock.send(bytes[idx:])

sock.close()