# CPSC 452

## Assignment 2
<br>

## Team Members
1. Raileen Del Rosario - raileendr@csu.fullerton.edu
2. Michael Lau - m.lau@csu.fullerton.edu
3. Garinn Morton - gmorton2@csu.fullerton.edu
4. Nafis Chowdhury - nafis195@csu.fullerton.edu
5. Ryan Romero - rromero26@csu.fullerton.edu
6. Jin Park - jinhpark9@csu.fullerton.edu
<br>

## Programming Language
C++
<br>

## Execution Process
`./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>`
* CIPHER NAME: The name of the cipher
    * DES: indicates the DES cipher
    * AES: indicates the AES cipher
* KEY: encryption key to use
    * Must be 16 characters representing a 64-bit HEX number for DES
    * Must be 128-bit number for AES
* ENC/DEC: whether to encrypt or decrypt, respectively
    * ENC: encrypt
    * DEC: decrypt
* INPUT FILE: the file from which to read the input
* OUTPUT FILE: the file to which to write the output
<br>

## Example for DES/AES encryption

* DES encryption: `./cipher DES "0123456789abcdef" ENC in.txt enc.txt`
* AES encryption: `./cipher AES "00112233445566778899aabbccddeeff" ENC in.txt enc.txt`
<br>

## Extra Credit
We did not implement the extra credit
<br>

## Special Notes
We used the openssl library, which is a powerful cryptographic library and widely used in the real world.
<br>