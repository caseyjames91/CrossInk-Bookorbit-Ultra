# CrossInk Home v0.1 — development status

This source snapshot is **not flashable**. It contains the earlier metadata/grid foundation plus a grid touch-safety correction.

## Verified this pass
- Inspected `BookOrbitCatalogBrowserActivity::buildListScreen` and `render`.
- Confirmed the catalog still renders through `FreeInkApp` list rows; the grid geometry is not yet connected to the catalog renderer or touch router.
- Hardened `BookOrbitGridLayout::hitTestPage`: reject touches in the bottom button-hint band and invalid page offsets, rather than allowing those touches to activate a book.
- Added regression assertions and passed `g++ -std=c++17 -Wall -Wextra -Werror tests/host/test_bookorbit_grid.cpp`.

## Next required integration
1. Add grid/list display mode to catalog state and options.
2. Render actual book cards with cover bitmaps and title/author from catalog entries.
3. Register grid card hit areas with the same UI interaction system as the list; don't draw a grid over existing list touch targets.
4. Adapt button navigation and pagination to visible grid cells, including server paging.
5. Build a Book Details activity, then run the full PlatformIO X4 Pro build.

The cover revision field is metadata only. It does not by itself download or render covers.
