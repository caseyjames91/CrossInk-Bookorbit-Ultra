#pragma once

// Pure layout math for the BookOrbit cover-grid browser. No network, heap or
// display dependencies: safe to use from both the renderer and touch router.
#include <algorithm>

namespace bookorbit_grid {
struct Cell {
  int x, y, width, height;
};
struct Layout {
  int columns = 3;
  int gap = 10;
  int left = 12;
  int top = 52;
  int right = 12;
  int bottom = 35;
  int titleHeight = 38;
  int coverRatioWidth = 2;
  int coverRatioHeight = 3;
};
inline int columnWidth(int screenWidth, const Layout& l) {
  const int cols = std::max(1, l.columns);
  return std::max(1, (screenWidth - l.left - l.right - (cols - 1) * l.gap) / cols);
}
inline int coverHeight(int screenWidth, const Layout& l) {
  return columnWidth(screenWidth, l) * l.coverRatioHeight / l.coverRatioWidth;
}
inline int rowHeight(int screenWidth, const Layout& l) { return coverHeight(screenWidth, l) + l.titleHeight + l.gap; }
inline int visibleRows(int screenWidth, int screenHeight, const Layout& l) {
  return std::max(1, (screenHeight - l.top - l.bottom + l.gap) / rowHeight(screenWidth, l));
}
inline int pageSize(int screenWidth, int screenHeight, const Layout& l) {
  return std::max(1, l.columns) * visibleRows(screenWidth, screenHeight, l);
}
inline int pageStart(int selected, int screenWidth, int screenHeight, const Layout& l) {
  const int size = pageSize(screenWidth, screenHeight, l);
  return std::max(0, selected) / size * size;
}
inline int moveSelection(int selected, int direction, int count, const Layout& l) {
  if (count <= 0) return -1;
  const int cols = std::max(1, l.columns);
  const int current = std::clamp(selected, 0, count - 1);
  int target = current;
  switch (direction) {
    case 0:
      target = current - cols;
      break;  // up
    case 1:
      target = current + cols;
      break;  // down
    case 2:
      target = current - 1;
      break;  // left
    case 3:
      target = current + 1;
      break;  // right
    default:
      break;
  }
  return std::clamp(target, 0, count - 1);
}
inline Cell cell(int index, int screenWidth, const Layout& l) {
  const int w = columnWidth(screenWidth, l);
  return {l.left + (index % std::max(1, l.columns)) * (w + l.gap),
          l.top + (index / std::max(1, l.columns)) * rowHeight(screenWidth, l), w,
          coverHeight(screenWidth, l) + l.titleHeight};
}
inline int hitTest(int x, int y, int count, int screenWidth, const Layout& l) {
  if (x < l.left || y < l.top || count <= 0) return -1;
  const int w = columnWidth(screenWidth, l);
  const int strideX = w + l.gap;
  const int strideY = rowHeight(screenWidth, l);
  if (strideX <= 0 || strideY <= 0) return -1;
  const int col = (x - l.left) / strideX;
  const int row = (y - l.top) / strideY;
  if (col < 0 || col >= std::max(1, l.columns) || (x - l.left) % strideX >= w ||
      (y - l.top) % strideY >= coverHeight(screenWidth, l) + l.titleHeight)
    return -1;
  const int index = row * std::max(1, l.columns) + col;
  return index < count ? index : -1;
}
// Converts a touch coordinate on a paginated grid to an absolute catalog index.
inline int hitTestPage(int x, int y, int start, int count, int screenWidth, int screenHeight, const Layout& l) {
  if (start < 0 || start >= count || y >= screenHeight - l.bottom) return -1;
  const int remaining = std::max(0, count - start);
  const int visible = std::min(remaining, pageSize(screenWidth, screenHeight, l));
  const int local = hitTest(x, y, visible, screenWidth, l);
  return local < 0 ? -1 : start + local;
}
}  // namespace bookorbit_grid
