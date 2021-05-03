#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;
int main(int argc, char** argv)
{
	string userinput;
	//DES or AES
	string cipherName = argv[1];
	//key
	string keyInput = argv[2];
	//ENC or DEC
	string funcType = argv[3];
	// input file
	string inputFile = argv[4];
	//output file
	string outputFile = argv[5];
	// Default block size
	int blockSize = -1;
	CipherInterface* cipher = NULL;
	
	if(cipherName == "DES") {
		// Set the block size to 64 bits
		blockSize = 8;
		cipher = new DES();

		/* Error checks */
		if(!cipher){
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		// setting the key (has to be casted)
		cipher->setKey((unsigned char*)keyInput.c_str());
	}
	else if(cipherName == "AES"){
		blockSize = 16;
		cipher = new AES();
		if(!cipher){
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		cipher->setKey((unsigned char*)keyInput.c_str());
	}
	
	unsigned char block[blockSize];
	// opens input.txt and reads the "raw bytes" (rb)
	FILE* inputFP = fopen(inputFile.c_str(), "rb");
	// creates output.txt and writes the "raw bytes" (wb)
	FILE* outputFP = fopen(outputFile.c_str(), "wb");
	// The number of bytes read
	int bytesReadIn = -1;
	//number of bytes written
	int bytesWrittenIn = -1;
	// The processed text
	unsigned char* text = NULL;
	
	// Read until end of file(eof) is reached
	while(!feof(inputFP)) {
		// Read a block
		bytesReadIn = fread(block, 1, blockSize, inputFP);
		
		// enc or dec the bytes that have been read in
		if(bytesReadIn != 0) {
			if(funcType == "ENC") {
				// padding the unused bytes within the block
				for(int i = bytesReadIn; i < blockSize; i++)
					block[i] = '0';	
				
				text = cipher->encrypt((const unsigned char*)block);		
			}
		        if(funcType == "DEC") text = cipher->decrypt((const unsigned char*)block);	
						
			//write the raw bytes
			bytesWrittenIn = fwrite(text, 1, blockSize, outputFP); 
		}
	}
	return 0;
}

	

