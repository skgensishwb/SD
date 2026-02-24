#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "basefile.hpp"
#include "../../lab1/src/mystring.hpp"

bool BaseFile::isOpen() {
    return (m_file != nullptr);
}

bool BaseFile::canRead() {
    return (m_file != nullptr) && (access(m_path.cStr(), R_OK) == 0); //
}

bool BaseFile::canWrite() {
    return (m_file != nullptr) && (access(m_path.cStr(), W_OK) == 0); //
}

size_t BaseFile::writeRaw(const void *buf, size_t nBytes) {
    return fwrite(buf, 1, nBytes, m_file);
}

size_t BaseFile::readRaw(void *buf, size_t maxBytes) {
    return fread(buf, 1, maxBytes, m_file);
}

long BaseFile::tell() {
    return ftell(m_file);
}

bool BaseFile::seek(long offset) { //
    return (fseek(m_file, offset, SEEK_SET) == 0);
}

size_t BaseFile::read(void *buf, size_t maxBytes) {
    return readRaw(buf, maxBytes);
}

size_t BaseFile::write(const void *buf, size_t nBytes) {
    return writeRaw(buf, nBytes);
}

BaseFile::BaseFile() : m_file(nullptr) {
    m_path.copyString("");
    std::cout << "Default constructor" << std::endl;
}

BaseFile::BaseFile(const char* filePath, const char* mode) : m_file(nullptr) {
    m_path.copyString(filePath);
    m_file = fopen(filePath, mode);
    std::cout << "Constructor with parameters" << std::endl;
}

BaseFile::BaseFile(FILE* filePtr) : m_file(filePtr) {
    m_path.copyString("<external>");
    std::cout << "Constructor with FILE" << std::endl;
}

BaseFile::~BaseFile() {
    if (m_file != nullptr) {
        fclose(m_file);
        m_file = nullptr;
    }
}

// -------------------------------------------------------------------------------------- //

int Base32File::encoded32Size(int rawSize) {
    return ((rawSize*8+4)/5);
}

int Base32File::decoded32Size(int encodeSize) {
    return (encodeSize*5/8);
}

int Base32File::encode32(const char *rawData, int rawSize, MyString* dst) {
    if (dst == nullptr || rawData == nullptr) {
        return 1;
    }
    if (rawSize < 0) {
        return 1;
    }
    if (rawSize == 0) {
        return 0;
    }

    int encodedLen = encoded32Size(rawSize);
    char* tmpBuf = new char[encodedLen + 1];
    
    unsigned int buffer = 0;
    int bitsInBuffer = 0;
    int dstIndex = 0;

    for (int i = 0; i < rawSize; i++) {
        unsigned int current_byte = static_cast<unsigned char>(rawData[i]);
        buffer = (buffer << 8) | current_byte;
        bitsInBuffer += 8;

        while (bitsInBuffer >= 5) {
            unsigned int result = (buffer >> (bitsInBuffer - 5)) & 0x1F;
            tmpBuf[dstIndex] = m_table[result];

            bitsInBuffer -= 5;
            dstIndex++;

            buffer &= (1U << bitsInBuffer) - 1;
        }
    }

    if (bitsInBuffer > 0) {
        unsigned int result = (buffer << (5 - bitsInBuffer)) & 0x1F;
        tmpBuf[dstIndex] = m_table[result];
        dstIndex++;
    }

    tmpBuf[dstIndex] = '\0';
    dst->copyString(tmpBuf);
    delete[] tmpBuf;

    return 0;
}

int Base32File::decode32(const char *encodedData, int encodedSize, MyString* dst) { // записывает в dst
    if (encodedData == nullptr || dst == nullptr) {
        return 1;
    }
    if (encodedSize < 0) {
        return 1;
    }
    if (encodedSize == 0) {
        return 0;
    }

    int decodingTable[256];
    for (int i = 0; i < 256; i++) {
        decodingTable[i] = -1;
    }

    for (int i = 0; i < 32; i++) {
        decodingTable[(unsigned char)m_table[i]] = i;
    }

    int decodedLen = decoded32Size(encodedSize);
    char* tmpBuf = new char[decodedLen + 1];

    unsigned int buffer = 0;
    int bitsInBuffer = 0;
    int dstIndex = 0;  

    for (int i = 0; i < encodedSize; ++i) {
        unsigned char currentChar = static_cast<unsigned char>(encodedData[i]);
        
        int five_bits = decodingTable[currentChar];
        if (five_bits == -1) {
            delete[] tmpBuf;
            return 2;
        }

        buffer = (buffer << 5) | five_bits;
        bitsInBuffer += 5;

        while (bitsInBuffer >= 8) {
            unsigned char byte = (buffer >> (bitsInBuffer - 8)) & 0xFF;
            tmpBuf[dstIndex] = (char)byte;
            dstIndex++;

            bitsInBuffer -= 8;
            buffer &= (1U << bitsInBuffer) - 1;
        }
    }

    tmpBuf[dstIndex] = '\0';
    dst->copyString(tmpBuf);
    delete[] tmpBuf;

    return 0;
}

size_t Base32File::write(const void *buf, size_t nBytes) {
    if (!canWrite() || nBytes == 0) {
        return 0;
    }

    MyString encoded;
    int result = encode32((const char*)buf, (int)nBytes, &encoded);
    if (result != 0) {
        return 0;
    }

    int encodedLen = encoded32Size((int)nBytes);
    size_t written = writeRaw(encoded.getString(), encodedLen);

    if ((int)written == encodedLen) {
        return nBytes;
    }

    return 0;
}

size_t Base32File::read(void *buf, size_t maxBytes) {
    if (!canRead() || maxBytes == 0) {
        return 0;
    }

    int encodedLen = encoded32Size((int)maxBytes);

    char* encodedBuf = new char[encodedLen + 1];
    size_t actualRead = readRaw(encodedBuf, encodedLen);

    if (actualRead == 0) {
        delete[] encodedBuf;
        return 0;
    }
    encodedBuf[actualRead] = '\0';

    MyString decoded;
    int result = decode32(encodedBuf, (int)actualRead, &decoded);
    delete[] encodedBuf;

    if (result != 0) {
        return 0;
    }

    char* decodedStr = decoded.getString();
    int decodedLen = decoded.len(decodedStr);
    size_t toCopy = (size_t)decodedLen < maxBytes ? (size_t)decodedLen : maxBytes;
    for (size_t i = 0; i < toCopy; i++) {
        ((char*)buf)[i] = decodedStr[i];
    }

    return toCopy;
}

static void setDefaultTable(char* table) {
    const char* def = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    for (int i = 0; i < 32; i++) {
        table[i] = def[i];
    }
    table[32] = '\0';
}

Base32File::Base32File() : BaseFile() {
    setDefaultTable(m_table);
    std::cout << "Base32File: Default constructor" << std::endl;
}

Base32File::Base32File(const char* filePath, const char* mode) : BaseFile(filePath, mode) {
    setDefaultTable(m_table);
    std::cout << "Base32File: Constructor with parameters" << std::endl;
}

Base32File::Base32File(const char* filePath, const char* mode, const char* table)
    : BaseFile(filePath, mode)
{
    for (int i = 0; i < 32; i++) {
        m_table[i] = table[i];
    }
    m_table[32] = '\0';
    std::cout << "Base32File: Constructor with custom table" << std::endl;
}

Base32File::~Base32File() {
    std::cout << "Base32File: Destructor" << std::endl;
}

// -------------------------------------------------------------------------------------- //

size_t RleFile::write(const void *buf, size_t nBytes) {
    if (!canWrite() || nBytes == 0) {
        return 0;
    }

    char* encoded = nullptr;
    int encodedSize = 0;

    int result = encodeRLE((const char*)buf, (int)nBytes, &encoded, &encodedSize);
    if (result != 0) {
        return 0;
    }

    size_t written = writeRaw(encoded, encodedSize);
    delete[] encoded;

    // Если всё записали — значит все исходные байты были обработаны
    if ((int)written == encodedSize) {
        return nBytes;
    }

    return 0;
}

size_t RleFile::read(void *buf, size_t maxBytes) {
    if (!canRead() || maxBytes == 0) {
        return 0;
    }

    size_t decoded = 0;
    char* out = (char*)buf;

    // Сначала дописываем остаток от предыдущей незавершённой серии
    while (m_pendingCount > 0 && decoded < maxBytes) {
        out[decoded] = m_pendingByte;
        decoded++;
        m_pendingCount--;
    }

    // Читаем новые пары [count][byte] из файла
    char pair[2];
    while (decoded < maxBytes) {
        size_t r = readRaw(pair, 2);
        if (r < 2) {
            break; // конец файла
        }

        int count = (unsigned char)pair[0];
        char byte = pair[1];

        int j = 0;
        while (j < count && decoded < maxBytes) {
            out[decoded] = byte;
            decoded++;
            j++;
        }

        // Если серия не уместилась целиком — сохраняем остаток
        if (j < count) {
            m_pendingCount = (unsigned char)(count - j);
            m_pendingByte = byte;
        }
    }

    return decoded;
}

int RleFile::encodeRLE(const char *rawData, int rawSize, char** dst, int* dstSize) {
    if (rawData == nullptr || rawSize <= 0 || dst == nullptr || dstSize == nullptr) {
        return 1;
    }

    // В худшем случае каждый байт даёт пару [1][byte], т.е. размер * 2
    char* buf = new char[rawSize * 2];
    int outIndex = 0;

    int i = 0;
    while (i < rawSize) {
        char current = rawData[i];
        int count = 1;

        // Считаем сколько подряд одинаковых байт (максимум 255)
        while (i + count < rawSize && rawData[i + count] == current && count < 255) {
            count++;
        }

        buf[outIndex++] = (char)count;
        buf[outIndex++] = current;
        i += count;
    }

    *dst = buf;
    *dstSize = outIndex;
    return 0;
}

int RleFile::decodeRLE(const char *encodedData, int encodedSize, char** dst, int* dstSize) {
    if (encodedData == nullptr || encodedSize <= 0 || dst == nullptr || dstSize == nullptr) {
        return 1;
    }

    // Сначала посчитаем итоговый размер
    int totalSize = 0;
    for (int i = 0; i < encodedSize; i += 2) {
        if (i + 1 >= encodedSize) {
            return 2; // нечётное количество байт — битые данные
        }
        totalSize += (unsigned char)encodedData[i];
    }

    char* buf = new char[totalSize];
    int outIndex = 0;

    for (int i = 0; i < encodedSize; i += 2) {
        int count = (unsigned char)encodedData[i];
        char byte = encodedData[i + 1];

        for (int j = 0; j < count; j++) {
            buf[outIndex++] = byte;
        }
    }

    *dst = buf;
    *dstSize = outIndex;
    return 0;
}

RleFile::RleFile() : BaseFile(), m_pendingCount(0), m_pendingByte(0) {
    std::cout << "RleFile: Default constructor" << std::endl;
}

RleFile::RleFile(const char* filePath, const char* mode)
    : BaseFile(filePath, mode), m_pendingCount(0), m_pendingByte(0)
{
    std::cout << "RleFile: Constructor with parameters" << std::endl;
}

RleFile::~RleFile() {
    std::cout << "RleFile: Destructor" << std::endl;
}

int intToStr(int number, char* buf, int bufSize) {
    int i = 0;
    bool negative = false;

    if (number < 0) {
        negative = true;
        number = -number;
    }
    if (number == 0) {
        buf[i++] = '0';
    }
    // Собираем цифры в обратном порядке
    char tmp[20];
    int count = 0;
    while (number > 0 && count < 20) {
        tmp[count++] = '0' + (number % 10);
        number /= 10;
    }
    // Знак минуса
    if (negative && i < bufSize) {
        buf[i++] = '-';
    }
    // Переворачиваем цифры
    for (int j = count - 1; j >= 0 && i < bufSize; j--) {
        buf[i++] = tmp[j];
    }
    buf[i] = '\0';
    return i;
}

// Вспомогательная: размер файла
long fileSize(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long s = ftell(f);
    fclose(f);
    return s;
}