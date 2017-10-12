//
//  BMP.cpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <array>
#include <fstream>
#include <iostream>

#include "throw_assert.hpp"

#include "BMP.hpp"

BMP::~BMP() {}

RGBColor BMP::getColor(int x, int y) const {
  if (m_data.empty()) {
    return (RGBColor){0, 0, 0};
  }
  
  RGBColor result = (RGBColor){0, 0, 0};
  
  if (x >= 0 && y >= 0 &&
      x <= m_width && y <= m_height)
  {
    size_t redIndex, greenIndex, blueIndex;
    __getIndicesForPixel(x, y, redIndex, greenIndex, blueIndex);
    
    if (blueIndex < m_data.size()) {
      result.r = m_data[redIndex];
      result.g = m_data[greenIndex];
      result.b = m_data[blueIndex];
    }
  }
  return result;
}

void BMP::setColor(int x, int y, const RGBColor& color) {
  if (x >= 0 && y >= 0 &&
      x <= m_width && y <= m_height)
  {
    size_t redIndex, greenIndex, blueIndex;
    __getIndicesForPixel(x, y, redIndex, greenIndex, blueIndex);
    
    if (blueIndex < m_data.size()) {
      m_data[redIndex]   = color.r;
      m_data[greenIndex] = color.g;
      m_data[blueIndex]  = color.b;
    }
  }
}

void BMP::__getIndicesForPixel(int x, int y, size_t& r_out, size_t& g_out, size_t& b_out) const {
  if (x >= 0 && y >= 0 &&
      x <= m_width && y <= m_height)
  {
    size_t pixelDataSize = m_colorDepth / (sizeof(char) * 8);
    r_out = m_width * y * pixelDataSize + x * pixelDataSize + 2;
    g_out = r_out - 1;//m_width * x + y * pixelDataSize + 1;
    b_out = r_out - 2;//m_width * x + y * pixelDataSize + 0;
  }
}

void BMP::save(const char* filepath) const {
  throw_assert_explain(!m_data.empty(), "[BMP] no data to save");
  throw_assert_explain(!m_header.empty(), "[BMP] no header in bmp to save");

  std::ofstream file(filepath, std::ios::binary);
  
  file.write(&m_header[0], m_header.size() * sizeof(char));
  file.write(&m_data[0], m_data.size() * sizeof(char));
  file.write(&m_restData[0], m_restData.size() * sizeof(char));
}

bool BMP::read(const char* filepath) {
  static constexpr int HEADER_SIZE = 54;

  std::ifstream bmp(filepath, std::ios::binary);
  throw_assert_explain(bmp.is_open(), "can not read the file: %s", filepath);

  std::vector<char> header(HEADER_SIZE);
  bmp.read(header.data(), header.size());
  
  bool headerIsFine = header.size() >= 2 && header[0] == 'B' && header[1] == 'M';
  throw_assert_explain(headerIsFine, "header is not of BMP file");
  
  m_header = header;
  
  // Read pixels
  auto fileSize   = *reinterpret_cast<uint32_t *>(&header[2]);
  auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
  auto width      = abs(*reinterpret_cast<int32_t *>(&header[18]));
  auto height     = abs(*reinterpret_cast<int32_t *>(&header[22]));
  auto depth      = *reinterpret_cast<uint16_t *>(&header[28]);
  
  m_colorDepth = depth;
  m_width = width;
  m_height = height;
  
  int offsetDataSize = dataOffset - HEADER_SIZE;
  m_offsetData.resize(offsetDataSize);
  
  bmp.read(m_offsetData.data(), m_offsetData.size());
  
  int dataSize = fileSize - HEADER_SIZE - offsetDataSize;

  std::vector<char> img;
  img.resize(dataSize);
  bmp.read(img.data(), img.size());
  
  m_data = img;
  
  for(char n; bmp >> n; ) {
    m_restData.push_back(n);
  }
  
  return true;
}
