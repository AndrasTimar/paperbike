#pragma once

struct Size
{
  int width;
  int height;

  Size(int width, int height) : width(width), height(height) {}

  bool operator==(const Size &other) const
  {
    return width == other.width && height == other.height;
  }
};