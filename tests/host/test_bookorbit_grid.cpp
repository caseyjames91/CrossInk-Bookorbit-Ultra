#include "../../src/components/BookOrbitGridLayout.h"
#include <cassert>
int main() {
  bookorbit_grid::Layout l;
  assert(bookorbit_grid::columnWidth(480, l) > 0);
  for (int i = 0; i < 6; ++i) {
    auto c = bookorbit_grid::cell(i, 480, l);
    assert(bookorbit_grid::hitTest(c.x + c.width / 2, c.y + c.height / 2, 6, 480, l) == i);
  }
  assert(bookorbit_grid::pageSize(480, 800, l) >= 3);
  assert(bookorbit_grid::pageStart(0, 480, 800, l) == 0);
  assert(bookorbit_grid::moveSelection(0, 1, 10, l) == 3);
  assert(bookorbit_grid::moveSelection(9, 1, 10, l) == 9);
  assert(bookorbit_grid::moveSelection(0, 0, 10, l) == 0);
  auto first = bookorbit_grid::cell(0, 480, l);
  assert(bookorbit_grid::hitTestPage(first.x + 5, first.y + 5, 6, 12, 480, 800, l) == 6);
  assert(bookorbit_grid::hitTestPage(first.x + 5, first.y + 5, 12, 12, 480, 800, l) == -1);
  assert(bookorbit_grid::hitTest(0, 0, 6, 480, l) == -1);
  assert(bookorbit_grid::hitTest(470, 400, 6, 480, l) == -1);
  assert(bookorbit_grid::hitTestPage(first.x + 5, 799, 0, 12, 480, 800, l) == -1);
  assert(bookorbit_grid::hitTestPage(first.x + 5, first.y + 5, -1, 12, 480, 800, l) == -1);
}
