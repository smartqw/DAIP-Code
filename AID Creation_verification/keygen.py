from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Hash import SHA256
import hashlib
import string
import secrets



file_k1=open("user_k1.txt","wb")
file_k2=open("user_k2_O.txt", "wb")
file_k_O=open("user_k_O.txt", "wb")
file_PseudoID=open("Pseudo_ID.txt", "w")
file_PseudoID_tilda=open("Pseudo_ID_tilda.txt", "w")
file_nonce=open("nonce.txt", "w")
User_ID="12345600000000000000"

#Generation of both Key for user and Key for organization and A_CERT Encryption Key

k1 = get_random_bytes(32) # Use a stored / generated key
k2_O = get_random_bytes(32)
h = hashlib.sha256()
h.update(k1+k2_O)
key_O=bytearray.fromhex(h.hexdigest())
file_k1.write(k1)
file_k2.write(k2_O)
file_k_O.write(key_O)

#Generation of organization parameter
alphabet = string.ascii_letters + string.digits

# Creation of PseudoID()
r= ''.join(secrets.choice(alphabet) for i in range(32))
temp=User_ID+r
h = SHA256.new()
h.update(bytes(temp, 'UTF-8'))
file_PseudoID.write("The Pseduo ID is \n")
file_PseudoID.write(h.hexdigest())

#Generation of PseudoID_Tilda()
nonce_o= ''.join(secrets.choice(alphabet) for i in range(32))
temp1= User_ID+nonce_o
h1=SHA256.new()
h1.update(bytes(temp1, 'UTF-8'))

file_nonce.write(nonce_o)
file_PseudoID_tilda.write("The Pseudo ID tilda is\n")
file_PseudoID_tilda.write(h1.hexdigest())




