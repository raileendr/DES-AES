#include "AES.h"

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
// ==========================================================================================================
// ==========================================================================================================
// ==========================================================================================================

/** Sets the key to use  @param key - the first byte of this represents whether encrypt/decrypt. 
 * 00 = encrypt, any other value = decrypt. Then come the bytes of the 128-bit key
 * (should be 16 of them).  @return - True if the key is valid and False otherwise */
bool AES::setKey(const unsigned char* keyArray)
{
	// AES implementation of openssl cares about whether you are encrypting or decrypting when setting the key.
		// when encrypting, use: AES_set_encrypt_key(...)
		// when decrypting, use: AES_set_decrypt_key(...)
	
	// NOTE** will be given a 17 byte key.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h

	unsigned char* aesKey = new unsigned char[16]; //16 element array to hold key
	char* holder; //variable for block allocation
	int count = 0;

	// check if setKey(encryption)
	if (keyArray[0] == 0) {
		// Convert key to HexBytes
		for(int i = 1; i <17; i++) {
			aesKey[i-1] = twoCharToHexByte(keyArray[i]);
		}
		// Set the encryption key (and error check)
		if (AES_set_encrypt_key(aesKey, 128, &enc_key) != 0) {
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
		else {
			return true;
		}
	}
	// else, setKey(decryption)
	else {
		// Convert key to HexBytes
		for(int i = 1; i <17; i++) {
			aesKey[i-1] = twoCharToHexByte(keyArray[i]);
		}
		// Set the decryption key (and error check)
		if (AES_set_decrypt_key(aesKey, 128, &dec_key) != 0)
		{
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			return false;
		}
		else {
			return true;
		}
	}
}

/** Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	// 1. Dynamically allocate a block to store the ciphertext.
    	unsigned char enc_out = new unsigned char[16];

	//clear memory buffer
	memset(enc_out, 0, 16);

    	// 2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
    	AES_ecb_encrypt(enc_out, plainText, &enc_key, AES_ENCRYPT);

    	// 3. Return the pointer to the ciphertext
    	return enc_out;
}

/** Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	// 1. Dynamically allocate a block to store the plaintext.
    	unsigned char* dec_out = new unsigned char[16];

	// Clearing memory buffer
    	memset(dec_out, 0, 16);

	// 2. Use AES_ecb_decrypt(...) to decrypt the text (please see the URL in setKey(...)
	AES_ecb_decrypt(dec_out, cipherText, &dec_key, AES_DECRYPT);

	// 3. Return the pointer to the plaintext
    	return dec_out;
}

