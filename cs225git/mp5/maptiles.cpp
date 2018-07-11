/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> pts;
    pts.resize(theTiles.size());
    map<Point<3>,int> pointmap;
    for (unsigned i=0; i<pts.size(); i++)
    {
        pts[i].set(0, theTiles[i].getAverageColor().h/360);
        pts[i].set(1, theTiles[i].getAverageColor().s);
        pts[i].set(2, theTiles[i].getAverageColor().l);
        pointmap[pts[i]] = i;
    }
    KDTree<3> tree(pts);
    // output
    int num_rows = theSource.getRows();
    int num_columns = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(num_rows, num_columns);
    for (int i=0; i<num_rows; i++)
        for (int j=0; j<num_columns; j++)
        {
            HSLAPixel source_color = theSource.getRegionColor(i, j);
            // query point
            Point<3> query;
            query.set(0, source_color.h/360);
            query.set(1, source_color.s);
            query.set(2, source_color.l);
            Point<3> foundpoint = tree.findNearestNeighbor(query);
            int index = pointmap[foundpoint];
            mosaic->setTile(i, j, &theTiles[index]);
        }
    return mosaic;

}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
