no_of_nominee=10
message_file=open("message_o_"+str(no_of_nominee)+".txt", "r")
sign_file=open("sign_o_"+str(no_of_nominee)+".txt", "r")
nonce_file=open("nonce.txt", "r")
N_CERT=open("N_CERT"+str(no_of_nominee)+".txt", "w")

for line in message_file:
 N_CERT.write(line) 
sign=next(sign_file)
nonce=next(nonce_file)
N_CERT.write("\n begin signature \n")
N_CERT.write(sign)
N_CERT.write("\nend signature \n")
N_CERT.write("begin nonce \n")
N_CERT.write(nonce)
N_CERT.write("\nend nonce")


