import hashlib
from Crypto.PublicKey import RSA
#from os import random
from Crypto.Hash import SHA256
import secrets
import string
import time


def hash_file(filename):
   """"This function returns the SHA-1 hash
   of the file passed into it"""

   # make a hash object
   h = hashlib.sha512()

   # open file for reading in binary mode
   with open(filename,'rb') as file:

       # loop till the end of the file
       chunk = 0
       while chunk != b'':
           # read only 1024 bytes at a time
           chunk = file.read(1024)
           h.update(chunk)

   # return the hex representation of digest
   return h.digest()

#Generation of puublic, private key parameter by organization
#generate a 1024-bit RSA key-pair:

keyPair = RSA.generate(bits=1024)
#print(f"Public key:  (n={hex(keyPair.n)}, e={hex(keyPair.e)})")
#print(f"Private key: (n={hex(keyPair.n)}, d={hex(keyPair.d)})")


## RSA 1024 bits Signing of a message 
#The signature is 1024-bit integer (128 bytes, 256 hex digits).
start=time.time()
message = hash_file("RC_info.txt")
#print(message)

hash = int.from_bytes(message, byteorder='big')
signature = pow(hash, keyPair.d, keyPair.n)
#print("For DC_U the derived Signature: is", hex(signature))

RC_info=open("RC_info.txt", "r")
CERT_RC_U=open("CERT_RC_U", "w")
for line in RC_info:
 CERT_RC_U.write(line) 
CERT_RC_U.write("\nbegin signature \n")
CERT_RC_U.write(hex(signature))
CERT_RC_U.write("\nend signature \n")

end = time.time()
print(f"Runtime of CAP RC_CERT() the program is {end - start}")

m2 = hash_file("RC_info.txt")

hash = int.from_bytes(m2, byteorder='big')
hashFromSignature = pow(signature, keyPair.e, keyPair.n)
#print("Signature valid:", hash == hashFromSignature)














