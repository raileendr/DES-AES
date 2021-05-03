#include "AES.h"
#include <iostream>
using namespace std;

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */

 // Pulled from DES.cpp to assist with conversion. 
unsigned char AES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */
	if (character >= '0' && character <= '9')
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if (character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;
	/* Invalid character */
	else return 'z';
}


/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */

// Pulled from DES.cpp to assist with conversion. 
unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;

	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if ((singleByte = charToHex(twoChars[0])) == 'z')
	{
		/* Invalid digit */
		return 'z';
	}

	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);

	/* Conver the second character */
	if ((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z';

	/* Insert the second value into the lower nibble */
	singleByte |= secondChar;

	return singleByte;
}


/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.

	unsigned char* aes_key = new unsigned char[16];

	// Char array to hold split string
	char* nowChar;

	// Using a counter variable to keep track of the replacement of hex to bytes in regards to the array. 
	int count = 0;

	//  === === === === === === === === === === ==== ==== ==== ==== ==== ==== ====
	//   0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   
	//  === === === === === === === === === === ==== ==== ==== ==== ==== ==== ====

	//  ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== 
	//   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33  
	//  ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== 

	// Each byte is held by two boxes in the array.
	// The numbers denote the index of the box.
	// Since the first byte can be disregarded, we must disregard the indices of 0-1 when converting to hex.
	// We need to convert the keyArray into hex because the professor said so in Discord :) 
	// Therefore, our for loop should traverse through the indices of 2-33. 
	// We will increment by two indices at a time and increase the counter by 1. By doing so, we can go ahead and keep track of the remaining bytes leftover!

	for (int i = 2; i < 33; i) {

		string holder; // This string holds the characters to be converted.
		

		// Now we add the characters of the array into the string, two at a time. 
		holder += keyArray[i];
		holder += keyArray[i + 1];

		
		// This line then splits up the string into chars.
		nowChar = &holder[0];

		// Does not execute if the key max has been reached. 
		// Places the converted values into the key array, with our friend The Count keeping track for us. 
		if (count < 16) 
		{
			aes_key[count] = twoCharToHexByte((unsigned char*)nowChar);
		}

		count++;
		i = i + 2;

	}
	
	// Encryption key setting from myaes.cpp
	if (keyArray[0] == '0') {

		/* Set the encryption key */
		if (AES_set_encrypt_key(aes_key, 128, &enc_key) != 0) {
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			exit(-1);
		}
		else {
			return true;
		}
	}

	// Decryption key setting from myaes.cpp 
	else {

		/* Set the decryption key */
		if (AES_set_decrypt_key(aes_key, 128, &dec_key) != 0) {
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			exit(-1);
		}
		else {
			return true;
		}
	}

	return false;

}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{

	// Dynamically allocate a block to store the ciphertext.
	unsigned char* enc_out = new unsigned char[16];

	// Clearing memory buffer 
	memset(enc_out, 0, 16);

	// Encrypt the text
	AES_ecb_encrypt(plainText, enc_out, &enc_key, AES_ENCRYPT);

	// 	Return the pointer to the ciphertext
	return enc_out;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{


	// Dynamically allocate a block to store the plaintext.
	unsigned char* dec_out = new unsigned char[16];

	// Clearing memory buffer
	memset(dec_out, 0, 16);

	// Decrypt!
	AES_ecb_encrypt(cipherText, dec_out, &dec_key, AES_DECRYPT);

	// 	Return the pointer to the plaintext
	return dec_out;
}