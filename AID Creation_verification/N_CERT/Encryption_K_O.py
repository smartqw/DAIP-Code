from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Hash import SHA256
import hashlib
import time

start=time.time()
no_of_nominee=4
file_k_O=open("user_k_O.txt","rb")
key_O=file_k_O.read(32)

file_to_encrypt = "N_CERT"+str(no_of_nominee)+".txt"
buffer_size = 65536 # 64kb

# === Encrypt ===

# Open the input and output files
input_file = open(file_to_encrypt, 'rb')
output_file = open(file_to_encrypt + '.encrypted', 'wb')

# Create the cipher object and encrypt the data
cipher_encrypt = AES.new(key_O, AES.MODE_CFB)

# Initially write the iv to the output file
output_file.write(cipher_encrypt.iv)

# Keep reading the file into the buffer, encrypting then writing to the new file
buffer = input_file.read(buffer_size)
while len(buffer) > 0:
    ciphered_bytes = cipher_encrypt.encrypt(buffer)
    output_file.write(ciphered_bytes)
    buffer = input_file.read(buffer_size)

end = time.time()
print(f"Runtime of the program is {end - start}")
# Close the input and output files
input_file.close()
output_file.close()

# === Decrypt ===

# Open the input and output files
input_file = open(file_to_encrypt + '.encrypted', 'rb')
output_file = open(file_to_encrypt + '.decrypted', 'wb')

# Read in the iv
iv = input_file.read(16)

# Create the cipher object and encrypt the data
cipher_encrypt = AES.new(key_O, AES.MODE_CFB, iv=iv)

# Keep reading the file into the buffer, decrypting then writing to the new file
buffer = input_file.read(buffer_size)
while len(buffer) > 0:
    decrypted_bytes = cipher_encrypt.decrypt(buffer)
    output_file.write(decrypted_bytes)
    buffer = input_file.read(buffer_size)

# Close the input and output files
input_file.close()
output_file.close()

# === Proving the data matches (hash the files and compare the hashes) ===


def get_file_hash(file_path):
    block_size = 65536
    file_hash = hashlib.sha256()
    with open(file_path, 'rb') as f:
        fb = f.read(block_size)
        while len(fb) > 0:
            file_hash.update(fb)
            fb = f.read(block_size)
    return file_hash.hexdigest()

assert get_file_hash(file_to_encrypt) == get_file_hash(file_to_encrypt + '.decrypted'), 'Files are not identical'

