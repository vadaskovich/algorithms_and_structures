//
//  BMP.hpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef BMP_hpp
#define BMP_hpp

#include <vector>

struct RGBColor {
  RGBColor(unsigned char r_, unsigned char g_, unsigned char b_)
  : r(r_),
    g(g_),
    b(b_)
  { }
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

class BMP {
public:
  ~BMP();
  
  bool read(const char* filepath);
  
  RGBColor getColor(int x, int y) const;
  void setColor(int x, int y, const RGBColor& color);
  void save(const char* filepath);
  
  int width () { return m_width; }
  int height() { return m_height; }
  
private:
  void __getIndicesForPixel(int x, int y, size_t& r_out, size_t& g_out, size_t& b_out) const;
  int m_width;
  int m_height;
  int m_colorDepth;
  
  std::vector<char> m_header;
  std::vector<char> m_offsetData;
  std::vector<char> m_data;
  std::vector<char> m_restData;
};

#endif /* BMP_hpp */
