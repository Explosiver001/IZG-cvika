/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/
//osgManipulator - Copyright (C) 2007 Fugro-Jason B.V.

#ifndef OSGMANIPULATOR_IZG_TrackballDragger
#define OSGMANIPULATOR_IZG_TrackballDragger 1

//#include <osgManipulator/RotateCylinderDragger>
#include <IZG_RotateCylinderDragger.h>
#include <osgManipulator/RotateSphereDragger>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>

namespace osgManipulator {

/**
 * Dragger for performing rotation in all axes.
 */
class IZG_TrackballDragger : public CompositeDragger
{
    public:

        IZG_TrackballDragger(bool useAutoTransform=false);

        META_OSGMANIPULATOR_Object(osgManipulator,IZG_TrackballDragger)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /** Sets the width of the axis lines in pixels. */
        void setAxisLineWidth(float linePixelWidth);

        /** Retrieves the width of the axis lines in pixels. */
        float getAxisLineWidth() const { return _axisLineWidth; }

        /** Sets the height of the cylinders representing the axis lines for picking. */
        void setPickCylinderHeight(float pickCylinderHeight);

        /** Retrieves the height of the cylinders representing the axis lines for picking. */
        float getPickCylinderHeight() const { return _pickCylinderHeight; }

    protected:

        virtual ~IZG_TrackballDragger();

        osg::ref_ptr<IZG_RotateCylinderDragger> _xDragger;
        osg::ref_ptr<IZG_RotateCylinderDragger> _yDragger;
        osg::ref_ptr<IZG_RotateCylinderDragger> _zDragger;
        osg::ref_ptr<RotateSphereDragger>   _xyzDragger;

        float _axisLineWidth;
        float _pickCylinderHeight;

        osg::ref_ptr<osg::Geode> _geode;
        osg::ref_ptr<osg::Cylinder> _cylinder;
        osg::ref_ptr<osg::LineWidth> _lineWidth;
};


}

#endif
