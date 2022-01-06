// CLE encryption demo
//
// See the Certificateless library for Encryption and decryption
//
// Al riyami peterson model of CLE encryption

//./riyami <~/Downloads/pbc-0.5.14/param/a.param
//gcc Al_Riyami.c -o riyami -L. -lpbc -lgmp

#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/time.h>

//sha256 calculation
void str2sha256(char *digest,  const char *str, int length ) 
{
  SHA256_CTX c;
  SHA256_Init( &c );
  while ( length > 0 ) 
  {
    if ( length > 512 ) SHA256_Update( &c, str, 512 );
    else SHA256_Update( &c, str, length );

    length -= 512;
    str += 512;
  }

  SHA256_Final ( digest, &c );  
}



//Main program

int main(int argc, char **argv) {
  pairing_t pairing;
  element_t g, mpk0, X, Y, ID, temp;
  element_t public_key, U, V;
  element_t secret_key, sk;
  element_t check1, check2, usk, SID;
  
  //nominee variable declaration
  element_t nominee_X[10], nominee_Y[10], nominee_sk[10], nominee_usk[10], nominee_SID[10], nominee_HashID[10], nominee_U[10];
  unsigned char nominee_V[10][32];
  unsigned char nominee_decryption[10][32];
    
  //CAP Parameter initilization
  
  element_t CAP_X, CAP_Y, CAP_sk, CAP_usk, CAP_SID, CAP_HashID,CAP_U[2]; 
  unsigned char CAP_ID[]="9876543210";
  unsigned char CAP_V[2][32], CAP_decryption[2][32];

  
  //initilization of users and master key variables
  
  pbc_demo_pairing_init(pairing, argc, argv);

  element_init_G1(g, pairing);  
  element_init_G1(mpk0, pairing);
  element_init_G1(X, pairing);
  element_init_G1(Y, pairing);
  element_init_G1(ID, pairing);
  element_init_GT(check1, pairing);
  element_init_GT(check2, pairing);
  element_init_Zr(secret_key, pairing);
  element_init_Zr(sk, pairing);
  element_init_Zr(temp, pairing);
  element_init_G1(U, pairing);
  element_init_G1(V, pairing);
  element_init_G1(usk, pairing);
  element_init_G1(SID, pairing);
  
  
  
  //initilization of nominee pairing variables
  
  int no_of_nominee=10, ii=0;
   FILE *fp_nominee, *fp_CAP;
  fp_nominee = fopen ("nominee_10.txt", "w");  
  fp_CAP=fopen("data2.txt", "w");
  
  for (ii=0; ii<no_of_nominee; ii++)
  {
  element_init_G1(nominee_X[ii], pairing);
  element_init_G1(nominee_Y[ii], pairing);
  element_init_Zr(nominee_sk[ii], pairing);
  element_init_G1(nominee_usk[ii], pairing);
  element_init_G1(nominee_SID[ii], pairing);
  element_init_G1(nominee_HashID[ii], pairing);
  element_init_G1(nominee_U[ii], pairing);

  }
  
  //CAP parameter initilization
  
   element_init_G1(CAP_X, pairing);
  element_init_G1(CAP_Y, pairing);
  element_init_Zr(CAP_sk, pairing);
  element_init_G1(CAP_HashID, pairing);
  element_init_G1(CAP_usk, pairing);
  element_init_G1(CAP_SID, pairing);
  element_init_G1(CAP_U[0], pairing);
    element_init_G1(CAP_U[1], pairing);
  //creation of buffer of size 32 bytes for SHA256
  unsigned char *digest=malloc(SHA256_DIGEST_LENGTH);
  unsigned char *digest1=malloc(SHA256_DIGEST_LENGTH); 
  int var1;
 


  //other variable initilization
  
  //key is second partial key defined for the organization
  unsigned char *key="12345678998765432112345678998793";
  
  //data2 is concatination of random key k1 and IDu (k1||ID_u)
  
  unsigned char data22[][32]={"123455555555555555555", "55555566778884433333333"};
  unsigned char nominee_id[][32]={"123456789", "987654321", "1234566789", "234567891000", "435654321123456","34567543212345", "5647354213234567", "345267123456543", "23124563124356", "987654321123"};
  unsigned char relationship_id[][32]={"Brother", "Brother", "Brother", "Sister", "Sister","Sister", "Sister", "Brother-Son", "Brother-Son", "Brother-Son"};
  unsigned char user_ID[]="12345600000000000000";
    struct timeval begin, end;
    
  
  
  
  //generate system parameters
  element_random(g);
  //generate private key
  element_random(secret_key);
   element_mul_zn(mpk0, g, secret_key);
   //generate master public key 
  
    element_printf("system parameter g = %B\n", g);  
  element_printf("master private key s = %B\n", secret_key);
  element_printf("master public key mpk0 = %B\n", mpk0);
      

  //2. User's Key Gen phase
  
  
  //users seceret key
  

  element_random(sk);  
  element_printf("user's private key sk = %B\n", sk);
  
  // public key generation user's side publik key (X and Y)
  
  element_mul_zn(X, g, sk);
  element_printf(" user's public key  X Part = %B\n", X);
  
  element_mul_zn(Y, mpk0, sk);
      element_printf(" user's public key  Y Part = %B\n", Y);
      
  
        
  //User's Key Extraction phase
  
  element_from_hash(ID, user_ID, 20);
   //element_printf("ID hash = %B\n", ID);
   
   element_mul_zn(usk, ID, secret_key);
   element_printf("  user's partial  secret key provided by IBS usk = %B\n", usk);
   
   //decryption operation
   element_mul_zn(SID, usk, sk);
    element_printf(" The final user's key by conctinating both keys SID  = %B\n", SID);
   
   
  
     element_pairing(check1, mpk0, X);
   // element_printf("f(X, mpk0) = %B\n", check1);


  element_pairing(check2, Y, g);
  //element_printf("f(Y, g) = %B\n", check2);
     
   if (!element_cmp(check1, check2)) 
     {
        printf("pairing verifies\n");
     } 
  else 
     {
      printf("*pairing does not verify*\n"); 
      }
 
 
   
  //2. nominee KeyGEN() phase
  
  

  for (ii=0; ii<no_of_nominee; ii++)
  {
  
  element_random(nominee_sk[ii]);
  element_mul_zn(nominee_X[ii], g, nominee_sk[ii]);
  element_mul_zn(nominee_Y[ii], mpk0, nominee_sk[ii]);   
  }

  
  // Nominee Key Extraction Phase 
  
  
  for (ii=0; ii<no_of_nominee; ii++)
  {
  
   printf("The id length of nominee is %ld \n", strlen(nominee_id[ii]));
   element_from_hash(nominee_HashID[ii],nominee_id[ii], strlen(nominee_id[ii]));
   element_mul_zn(nominee_usk[ii], nominee_HashID[ii], secret_key);
   //Nominee final keys
   element_mul_zn(nominee_SID[ii],nominee_usk[ii], nominee_sk[ii]);
   element_pairing(check1, mpk0, nominee_X[ii]);
   element_pairing(check2, nominee_Y[ii], g);
     
   if (!element_cmp(check1, check2)) 
     {
        printf("pairing verifies\n of %s", nominee_id[ii]);
     } 
  else 
     {
      printf("*pairing does not verify*\n"); 
      }

  }

  

//CAP KeyGen() Phase

  element_random(CAP_sk);
  element_mul_zn(CAP_X, g, CAP_sk);
  element_mul_zn(CAP_Y, mpk0, CAP_sk);
  
//CAP Extraction() Phase
   element_from_hash(CAP_HashID, CAP_ID, strlen(CAP_ID));  
   element_mul_zn(CAP_usk, CAP_HashID, secret_key);
   element_mul_zn(CAP_SID, CAP_usk, CAP_sk);
 


  
  // Encryption Phase, encryption of k_2^o for desginated nominee

//gettimeofday(&begin, 0);
   for (ii=0; ii<no_of_nominee; ii++)
  {
   
   element_random(temp);  
   element_mul_zn(nominee_U[ii], g, temp);
   element_pairing(check1, nominee_Y[ii], nominee_HashID[ii]);
   element_pow_zn( check2, check1, temp);
   //element_printf("for nominee %d, G2 mapping is %B\n",ii, check2);
   int n = element_length_in_bytes(check2);
   int m = element_length_in_bytes(nominee_U[ii]);
   int i;
   
   unsigned char *buffer_U = pbc_malloc(m);
   unsigned char *data = pbc_malloc(n);
   element_to_bytes(buffer_U, nominee_U[ii]);
   element_to_bytes(data, check2);
        //for (i=0; i<n; i++)
     //{
       //printf("%2X", data[i]);
     
    // }
   str2sha256(digest, data, n);   
   int length=strlen(key);
  // printf("The encrypted data for nominee %d \n U part is %B \n", ii+1, nominee_U[ii]);  
      printf("\nThe encrypted data for nominee %d V part is \n", ii+1); 
     for ( var1 = 0; var1 < strlen(key); var1++ )
     {
        nominee_V[ii][var1]= key[var1]^digest[var1];
        printf("%c", nominee_V[ii][var1]);
      }
      
   fputs(nominee_id[ii],fp_nominee);
   fputs("\n", fp_nominee);
   fputs(relationship_id[ii],fp_nominee);
   fputs("\n", fp_nominee);
   fputs("preference level is ", fp_nominee);
   fprintf(fp_nominee, "%d", ii+1);
   fputs("\n", fp_nominee);
   fputs(buffer_U, fp_nominee);
   fputs("\n", fp_nominee);
   fputs(nominee_V[ii], fp_nominee); 
   fputs("\n", fp_nominee); 
  } 
  
  fputs("www.facebook.com", fp_nominee);
    //gettimeofday(&end, 0);
    
    //long seconds = end.tv_sec - begin.tv_sec;
    //long microseconds = end.tv_usec - begin.tv_usec;
    //double elapsed = seconds + microseconds*1e-6;
  //  
//    printf("Time measured: %.7f seconds.\n", elapsed);

    


//decryption for each nominee to recieve the key value
   

 for (ii=0; ii<no_of_nominee; ii++)  
 {
    element_pairing(check1, nominee_U[ii], nominee_SID[ii]);  
      //element_printf("for nominee %d, G2 mapping in decryption  %B\n",ii, check1);  
   int ram=element_length_in_bytes(check1);
    int j;
    unsigned char *data2 = pbc_malloc(ram);
        element_to_bytes(data2, check1);  
    
    //     for (j=0; j< ram; j++)
     //{
       //printf("%2X", data2[j]);
     
    // }
     
    str2sha256(digest1, data2, ram);  
    
    printf("the decrypted value for nominee %d is ", ii);   
      for ( var1 = 0; var1 < strlen(key); var1++ )
     {
        nominee_decryption[ii][var1]= nominee_V[ii][var1]^digest1[var1];
       printf("%c", nominee_decryption[ii][var1]);
      }
          
  printf("\n");
  
  }
  
    

//  CAP Encryption

//gettimeofday(&begin, 0); 
   for (ii=0; ii<2; ii++)
  {
   
   element_random(temp);  
   element_mul_zn(CAP_U[ii], g, temp);
   element_pairing(check1, CAP_Y, CAP_HashID);
   element_pow_zn( check2, check1, temp);
   //element_printf("for nominee %d, G2 mapping is %B\n",ii, check2);
   int n = element_length_in_bytes(check2);
   int m = element_length_in_bytes(CAP_U[ii]);
   int i;
   
   unsigned char *buffer_U = pbc_malloc(m);
   unsigned char *data = pbc_malloc(n);
   element_to_bytes(buffer_U, CAP_U[ii]);
   element_to_bytes(data, check2);
   str2sha256(digest, data, n);   
//printf("The encrypted data for CAP fragment %dth \n U part is %B \n", ii+1, CAP_U[ii]);  
      printf("The encrypted data for CAP fragment %dth V part is \n", ii+1); 

   int length=strlen(data22[ii]);   
     for ( var1 = 0; var1 < length; var1++ )
     {
        CAP_V[ii][var1]= data22[ii][var1]^digest[var1];
        printf("%c", nominee_V[ii][var1]);
      }
  //gettimeofday(&end, 0);
    //long seconds = end.tv_sec - begin.tv_sec;
    //long microseconds = end.tv_usec - begin.tv_usec;
    //double elapsed = seconds + microseconds*1e-6;
   //printf("\n Time measured: %.7f seconds.\n", elapsed); 
  
      
    fputs(buffer_U, fp_CAP);
    fputs("\n", fp_CAP);
    fputs(CAP_V[ii], fp_CAP);
    fputs("\n", fp_CAP);
      
  }  
    
  
  //CAP Decryption
 

  for (ii=0; ii<2; ii++)  
 {
   element_pairing(check1, CAP_U[ii], CAP_SID);  
      //element_printf("for nominee %d, G2 mapping in decryption  %B\n",ii, check1);  
   int ram=element_length_in_bytes(check1);
    int j;
    unsigned char *data2 = pbc_malloc(ram);
        element_to_bytes(data2, check1);  
   
    str2sha256(digest1, data2, ram);  
    
    printf("\nThe decrypted value for CAP [%d]", ii+1);   
      for ( var1 = 0; var1 < strlen(data22[ii]); var1++ )
     {
        CAP_decryption[ii][var1]= CAP_V[ii][var1]^digest1[var1];
       printf("%c", CAP_decryption[ii][var1]);

      }
      
  printf("\n");
  }  


  fclose(fp_nominee);
  fclose(fp_CAP);
          
  return 0;
}

//gcc Al_Riyami.c -o riyami -L. -lpbc -lgmp -lcrypto

