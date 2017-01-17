// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015, 2016.
// Modifications copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_HPP
#define BOOST_GEOMETRY_GEOMETRY_HPP

// Shortcut to include all header files

#include <Qt/boost/geometry/core/closure.hpp>
#include <Qt/boost/geometry/core/coordinate_dimension.hpp>
#include <Qt/boost/geometry/core/coordinate_system.hpp>
#include <Qt/boost/geometry/core/coordinate_type.hpp>
#include <Qt/boost/geometry/core/cs.hpp>
#include <Qt/boost/geometry/core/interior_type.hpp>
#include <Qt/boost/geometry/core/point_order.hpp>
#include <Qt/boost/geometry/core/point_type.hpp>
#include <Qt/boost/geometry/core/ring_type.hpp>
#include <Qt/boost/geometry/core/srs.hpp>
#include <Qt/boost/geometry/core/tag.hpp>
#include <Qt/boost/geometry/core/tag_cast.hpp>
#include <Qt/boost/geometry/core/tags.hpp>

// Core algorithms
#include <Qt/boost/geometry/core/access.hpp>
#include <Qt/boost/geometry/core/exterior_ring.hpp>
#include <Qt/boost/geometry/core/interior_rings.hpp>
#include <Qt/boost/geometry/core/radian_access.hpp>
#include <Qt/boost/geometry/core/radius.hpp>
#include <Qt/boost/geometry/core/topological_dimension.hpp>

#include <Qt/boost/geometry/arithmetic/arithmetic.hpp>
#include <Qt/boost/geometry/arithmetic/dot_product.hpp>

#include <Qt/boost/geometry/strategies/strategies.hpp>

#include <Qt/boost/geometry/algorithms/append.hpp>
#include <Qt/boost/geometry/algorithms/area.hpp>
#include <Qt/boost/geometry/algorithms/assign.hpp>
#include <Qt/boost/geometry/algorithms/buffer.hpp>
#include <Qt/boost/geometry/algorithms/centroid.hpp>
#include <Qt/boost/geometry/algorithms/clear.hpp>
#include <Qt/boost/geometry/algorithms/comparable_distance.hpp>
#include <Qt/boost/geometry/algorithms/convert.hpp>
#include <Qt/boost/geometry/algorithms/convex_hull.hpp>
#include <Qt/boost/geometry/algorithms/correct.hpp>
#include <Qt/boost/geometry/algorithms/covered_by.hpp>
#include <Qt/boost/geometry/algorithms/crosses.hpp>
#include <Qt/boost/geometry/algorithms/difference.hpp>
#include <Qt/boost/geometry/algorithms/disjoint.hpp>
#include <Qt/boost/geometry/algorithms/distance.hpp>
#include <Qt/boost/geometry/algorithms/envelope.hpp>
#include <Qt/boost/geometry/algorithms/equals.hpp>
#include <Qt/boost/geometry/algorithms/expand.hpp>
#include <Qt/boost/geometry/algorithms/for_each.hpp>
#include <Qt/boost/geometry/algorithms/intersection.hpp>
#include <Qt/boost/geometry/algorithms/intersects.hpp>
#include <Qt/boost/geometry/algorithms/is_empty.hpp>
#include <Qt/boost/geometry/algorithms/is_simple.hpp>
#include <Qt/boost/geometry/algorithms/is_valid.hpp>
#include <Qt/boost/geometry/algorithms/length.hpp>
#include <Qt/boost/geometry/algorithms/make.hpp>
#include <Qt/boost/geometry/algorithms/num_geometries.hpp>
#include <Qt/boost/geometry/algorithms/num_interior_rings.hpp>
#include <Qt/boost/geometry/algorithms/num_points.hpp>
#include <Qt/boost/geometry/algorithms/num_segments.hpp>
#include <Qt/boost/geometry/algorithms/overlaps.hpp>
#include <Qt/boost/geometry/algorithms/perimeter.hpp>
#include <Qt/boost/geometry/algorithms/relate.hpp>
#include <Qt/boost/geometry/algorithms/relation.hpp>
#include <Qt/boost/geometry/algorithms/remove_spikes.hpp>
#include <Qt/boost/geometry/algorithms/reverse.hpp>
#include <Qt/boost/geometry/algorithms/simplify.hpp>
#include <Qt/boost/geometry/algorithms/sym_difference.hpp>
#include <Qt/boost/geometry/algorithms/touches.hpp>
#include <Qt/boost/geometry/algorithms/transform.hpp>
#include <Qt/boost/geometry/algorithms/union.hpp>
#include <Qt/boost/geometry/algorithms/unique.hpp>
#include <Qt/boost/geometry/algorithms/within.hpp>

// check includes all concepts
#include <Qt/boost/geometry/geometries/concepts/check.hpp>

#include <Qt/boost/geometry/util/for_each_coordinate.hpp>
#include <Qt/boost/geometry/util/math.hpp>
#include <Qt/boost/geometry/util/select_coordinate_type.hpp>
#include <Qt/boost/geometry/util/select_most_precise.hpp>

#include <Qt/boost/geometry/views/box_view.hpp>
#include <Qt/boost/geometry/views/closeable_view.hpp>
#include <Qt/boost/geometry/views/identity_view.hpp>
#include <Qt/boost/geometry/views/reversible_view.hpp>
#include <Qt/boost/geometry/views/segment_view.hpp>

#include <Qt/boost/geometry/io/io.hpp>
#include <Qt/boost/geometry/io/dsv/write.hpp>
#include <Qt/boost/geometry/io/svg/svg_mapper.hpp>
#include <Qt/boost/geometry/io/svg/write.hpp>
#include <Qt/boost/geometry/io/wkt/read.hpp>
#include <Qt/boost/geometry/io/wkt/write.hpp>

#endif // BOOST_GEOMETRY_GEOMETRY_HPP
