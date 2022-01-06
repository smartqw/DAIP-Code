# DAIP-Code 
The simulation of DAIP model <br>
The simulation module has two subsections <br>
First is, the CLE Encryption which is based on PBC library. The execution of this program requires to install all PBC dependencies <br>
#The second is for AID creation, which is created in python. It call cryptodome library for using cryptographic primitives. The execution of it, requires to install the pycryptodome library as a dependencies. <br>
the parameter no._of_nominee needs to be set. The value can be 1 to 10. <br>


#Execution steps: <br>
---------------------------------<br>
Step 1: Execute the CLE__AID_nominee_sub.c to initlize KeyGen(), Key.Extract(), for IBS, CAP, Nominee and users. The programs also outputs the N_{receipt}.<br>
Step 2: Execute keygen.py to create k1, k2_o, k^o, psudo IDs, and nonce_o <br>
Step 3: Call Message_O_Generation to create a message_o  which containg nominee declaration information. <br>
Step 4: Execute sign.py. This files has signature scheme implemented by the organiztion to sign a message created in step 3. <br>
Step 5. Execute N_CERT.py to compute the N_CERT <br>
Step 6: Execute N_CERT/Encryption_K_O.py to encrypt N_CERT of step 5 to obtain A_cert. <br>
Step 7: Execute N_reciept/Encryption_K1.py to encrypt N_reciept derived in Step 1 to obtain A_info. <br> 
Step 8: Execute DC_U.py and RC_Nominee.py to generate death and relationship certificate. <br>
Step 9: Excute Hash_verification.py to verify the pseudo_ID_tilda.  <br>
