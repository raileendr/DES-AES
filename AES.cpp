#include "AES.h"

/** Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise */
bool AES::setKey(const unsigned char* keyArray)
{
	// TODO: AES implementation of openssl cares about whether you are encrypting or decrypting when setting the key.
		// when encrypting, use: AES_set_encrypt_key(...)
		// when decrypting, use: AES_set_decrypt_key(...)

	// if ( (keyArray[0] == 0) && (keyArray[1] == 00) ){
			// return !(AES_set_encrypt_key(AES_KEY, 128, &enc_key));
			// this returns zero on success and a negative number on error.
	//	} 
	//	else {
			// return !(AES_set_decrypt_key(AES_KEY, 128, &dec_key));
			// this returns zero on success and a negative number on error.
	//	}


	// NOTE** will be given a 17 byte key, where the first byte is used to indicate whether 
		// we are encrypting or decrypting. The rest of the bytes in the array indicate the 
		// 16 bytes of the 128-bit AES key. (only 128-bit AES required for this project)
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h

	return false;
}


/** Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	// 1. Dynamically allocate a block to store the ciphertext.
		// int* dynamicPtr;
		// dynamicPtr = new char[16?];


	// 2. Use AES_ecb_encrypt(...) to encrypt the text (see the URL in setKey() and the aes.cpp example provided)
	

	// 3. Return the pointer to the ciphertext
		// string ciphertext = "";
		// for (int i = 0; i <16; i++){
			// ciphertext = ciphertext + dynamicPtr[i];
		//	}
		//	delete[] dynamicPtr;
		// 	return ciphertext;


	return NULL;
}


/** Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	// 1. Dynamically allocate a block to store the plaintext.
		// int* dynamicPtr;
		// dynamicPtr = new char[16?];


	// 2. Use AES_ecb_encrypt(...) to decrypt the text (see the URL in setKey(...) )
	
	
	// 3. Return the pointer to the plaintext
		// string plaintext = "";
		// for (int i = 0; i <16; i++){
			// plaintext = plaintext + dynamicPtr[i];
		// }
		// delete[] dynamicPtr;
		// return plaintext

	return NULL;
}

