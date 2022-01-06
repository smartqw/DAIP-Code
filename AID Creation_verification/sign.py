import hashlib
from Crypto.PublicKey import RSA
#from os import random
from Crypto.Hash import SHA256
import secrets
import string
import time

no_of_nominee=10
#file_name=open("message_o_"+str(no_of_nominee)+".txt", "rb")
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




start=time.time()
#Hash of the file
message = hash_file("message_o_"+str(no_of_nominee)+".txt")
#print(message)

## RSA 1024 bits Signing of a message 
#The signature is 1024-bit integer (128 bytes, 256 hex digits).

hash = int.from_bytes(message, byteorder='big')
signature = pow(hash, keyPair.d, keyPair.n)

#print("For message_o the derived Signature: is", hex(signature))

#Writing sign to a file
f1=open("sign_o_"+str(no_of_nominee)+".txt", "w")
f1.write(hex(signature))


### Verification of signature

# RSA verify signature
m2 = hash_file("message_o_"+str(no_of_nominee)+".txt")

hash = int.from_bytes(m2, byteorder='big')
hashFromSignature = pow(signature, keyPair.e, keyPair.n)
#print("Signature valid:", hash == hashFromSignature)
end = time.time()
print(f"Sigma.Sign +Sigma.Verify() time of program is {end - start}")


