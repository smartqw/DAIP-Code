import hashlib
from Crypto.Hash import SHA256
import time

start=time.time()
file_PseudoID_tilda=open("Pseudo_ID_tilda.txt", "r")
file_nonce=open("nonce.txt", "r")
User_ID="12345600000000000000"
next(file_PseudoID_tilda)
pseudo_ID_tilda=next(file_PseudoID_tilda)
#print(pseudo_ID_tilda+"\n")
nonce_o=next(file_nonce)
#print(nonce_o+"\n")
temp1= User_ID+nonce_o
h1=SHA256.new()
h1.update(bytes(temp1, 'UTF-8'))
#print(h1.hexdigest()+"\n")
#print("Hash Verification is valid:", h1.hexdigest() == pseudo_ID_tilda)
end = time.time()
print(f"Runtime of Hashverification(ID+nonce) the program is {end - start}")

