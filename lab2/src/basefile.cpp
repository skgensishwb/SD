#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "basefile.hpp"
#include "../../lab1/src/mystring.hpp"

bool BaseFile::isOpen() {
    return (m_file != nullptr);
}

bool BaseFile::canRead() {
    return (m_file != nullptr) && (access(m_path.c_str(), R_OK) == 0); //
}

bool BaseFile::canWrite() {
    return (m_file != nullptr) && (access(m_path.c_str(), W_OK) == 0); //
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