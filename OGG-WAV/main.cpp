#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

using namespace std;

typedef struct Header {
    char riff[4];
    uint32_t fileSize;
    char wave[4];
    char fmt[4];
    uint32_t subChunk1Size;
    uint16_t AudioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4];
    uint32_t ChunkSize;
    uint32_t subChunk2Size;
};

typedef struct oggHeader{
    char CapturePattern[4];
    uint8_t Version;
    uint8_t headerType;
    uint64_t granulePosition;
    uint32_t bitstreamSerialNum;
    uint32_t PageSequenceNum;
    uint32_t Checksum;
    uint8_t PageSegment;
};

int getFileSize(FILE*inFile){
    int fileSize=0;
    fseek(inFile,0,SEEK_END);

    fileSize=ftell(inFile);

    fseek(inFile,0,SEEK_SET);
    return fileSize;
}

bool isWavFile(const string& filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".wav";
}

string determineType(const string& filePath) {
    if (isWavFile(filePath)) {
        return "WAV";
    } else
        return "OGG";
}

int main() {
    Header h;
    oggHeader OH;

    const char* filePath = "  ";  //Enter audio extension between " "

     string result = determineType(filePath);
    cout << "The File is: " << result << endl;


    if(result == "WAV"){
    ifstream file(filePath, ios::binary);
    FILE* wavFile = fopen(filePath, "r");

     int headerSize= sizeof(Header), filelength=0;
     filelength=getFileSize(wavFile);
     file.read(reinterpret_cast<char*>(&h), sizeof(Header));


    cout << "File size        : " <<filelength <<endl;
    cout << "ChunkID           : " << h.riff[0];
    cout << h.riff[1];
    cout << h.riff[2];
    cout << h.riff[3] << endl;
    cout << "chunkSize         : " << h.ChunkSize <<endl;

    cout << "Format            : " << h.wave[0];
    cout <<h.wave[1];
    cout <<h.wave[2];
    cout <<h.wave[3]<< endl;

    cout << "Sub-Chunk1ID      : " << h.fmt[0];
    cout << h.fmt[1];
    cout << h.fmt[2];
    cout << h.fmt[3]<< endl;
    cout << "SubChunk1Size     : " << h.subChunk1Size<< endl;
    cout << "Audio Format      : " << h.AudioFormat << endl;
    cout << "Channels          : " << h.numChannels << endl;
    cout << "Sample Rate       : " << h.sampleRate << endl;
    cout << "Byte Rate         : " << h.byteRate << endl;
    cout << "Block Align       : " << h.blockAlign << endl;
    cout << "Bits Per Sample   : " << h.bitsPerSample << endl;
    cout << "SubChunk2ID       : " << h.data[0];
    cout << h.data[1];
    cout << h.data[2];
    cout << h.data[3] << endl;
    cout << "SubChunk2Size     : " << h.sampleRate * h.numChannels * (h.bitsPerSample/8)<< endl;

    }


else{

       ifstream file(filePath, ios::binary);
        file.read(reinterpret_cast<char*>(&OH), sizeof(oggHeader));
        FILE* oggFile = fopen(filePath, "r");
       int headerSize= sizeof(oggHeader), filelength=0;
        filelength=getFileSize(oggFile);

        cout<< "File Length             : " <<filelength<<endl;
        cout<< "Capture Pattern         : " <<OH.CapturePattern[0];
        cout<< OH.CapturePattern[1];
        cout<< OH.CapturePattern[2];
        cout<< OH.CapturePattern[3]<<endl;
        cout<< "version                 : " <<static_cast<int>(OH.Version)<<endl;
        cout<< "Header Type             : " <<static_cast<int>(OH.headerType)<<endl;
        cout<< "Granule Position        : " <<OH.granulePosition<<endl;
        cout<< "Bitstream Serial Number : " <<OH.bitstreamSerialNum<<endl;
        cout<< "Page Sequence Number    : " <<OH.PageSequenceNum<<endl;
        cout<< "CheckSUm                : " <<OH.Checksum<<endl;
        cout<< "Page Segments           : " <<static_cast<int>(OH.PageSegment)<<endl;
        }

   return 0;
}


