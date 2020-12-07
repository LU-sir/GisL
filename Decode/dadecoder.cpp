//
// Created by beiyu on 2020-12-06.
//

#include <string>
#include <fstream>
#include <algorithm>
#include "dadecoder.h"

DaDecoder::DaDecoder() = default;

// Question: why string can not be in construct
DaDecoder::DaDecoder(const char filename[]) {
    getFilename(filename);
}

void DaDecoder::getFilename(const char encodeFilename[]) {
    this->filename = encodeFilename;
    this->buffer = nullptr;
    this->meaning = "";
    success = loadFile();
}

int DaDecoder::loadFile() {
    std::ifstream ifs;
    ifs.open(filename, std::ios::in | std::ios::binary);
    if (ifs.fail()) return 0;
    loadUnitInFile(ifs);
    meaning = decode();
    ifs.close();
    return 1;
}

void DaDecoder::loadUnitInFile(std::ifstream &ifs) {
    int filesize = findFilesize(ifs);
    buffer = new char[filesize];
    ifs.read(buffer, filesize);
    int positionInFile = 0;
    eraseUnits();
    for (int ii = 0; ii < unitCount; ii++) {
        DaUnit unit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
        positionInFile += 5;
        units.push_back(unit);
    }
}

// Question: erase units and receive next one
void DaDecoder::eraseUnits() {
    std::vector<DaUnit>::iterator iUnit;
    for (iUnit = units.begin(); iUnit != units.end();) {
        iUnit = units.erase(iUnit);
    }
}

int DaDecoder::findFilesize(std::ifstream &ifs) {
    ifs.seekg(0, std::ifstream::end);
    int filesize = static_cast<int>(ifs.tellg());
    ifs.seekg(0, std::ifstream::beg);
    unitCount = filesize / daUnitSize;
    return filesize;
}

std::string DaDecoder::decode() {
    std::sort(units.begin(), units.end(), DaUnit::isSmaller);
    return textInUnits();
}

std::string DaDecoder::textInUnits() {
    for (int ii = 0; ii < unitCount; ++ii) meaning.push_back(units[ii].value);
    return meaning;
}

void DaDecoder::writeIntoFile(const std::string &outfile) const {
    std::ofstream ofs(outfile);
//    ofs.write(meaning.c_str(), meaning.size());
    ofs << meaning;
    ofs.close();
}

DaDecoder::~DaDecoder() = default;
