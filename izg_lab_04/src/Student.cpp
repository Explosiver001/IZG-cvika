#include "Student.h"

#include <osg/Plane>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

osg::Vec3d projectOnPlane(const osg::Vec3d& point, const osg::Vec3d& planeNormal)
{
    return point - planeNormal * (point * planeNormal);
}

double dot(const osg::Vec3d& u, const osg::Vec3d& v)
{
    return u * v;
}

osg::Vec3d cross(const osg::Vec3d& u, const osg::Vec3d& v)
{
    return u ^ v;
}

void normalize(osg::Vec3d &v)
{
    v.normalize();
}

osg::Vec3d normalized(const osg::Vec3d& v)
{
    osg::Vec3d u(v);
    u.normalize();

    return u;
}

osg::Vec3d normalized()
{
    return osg::Vec3d();
}

#if USE_STUDENT_SOLUTION
osg::Matrix getScaleMatrix(const osg::Vec3d& scale)
{
    //Task 1 - fill in the scale matrix

    osg::Matrix m(  scale.x(), 0.0f, 0.0f, 0.0f,
                    0.0f, scale.y(), 0.0f, 0.0f,
                    0.0f, 0.0f, scale.z(), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    return m;
}

osg::Matrix getTranslationMatrix(const osg::Vec3d& translation)
{
    //Task 2 - fill in the translation matrix

    osg::Matrix m(  1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    translation.x(), translation.y(), translation.z(), 1.0f);

    return m;
}

osg::Matrix rotateAroundX(double angle)
{
    
    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 3 - fill in the rotation matrix around X axis

    osg::Matrix m(  1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, cosa, -sina, 0.0f,
                    0.0f, sina, cosa, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    return m;
}

osg::Matrix rotateAroundY(double angle)
{
    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 4 - fill in the rotation matrix around Y axis

    osg::Matrix m(  cosa, 0.0f, sina, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -sina, 0.0f, cosa, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    return m;
}

osg::Matrix rotateAroundZ(double angle)
{
    double sina = std::sin(angle);
    double cosa = std::cos(angle);

    //Task 5 - fill in the rotation matrix around Z axis

    osg::Matrix m(  cosa, -sina, 0.0f, 0.0f,
                    sina, cosa, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    return m;
}

double angleBetweenVectors(osg::Vec3d u, osg::Vec3d v)
{
    //Task 6
    //Normalize both vectors - method normalize()
    //Compute cosine of the angle between the vectors using the dot product - operator *
    //Return the angle using arcus cosine - function std::acos()

    u.normalize();
    v.normalize();
    
    auto uv = dot(u, v);
    //facha
    return std::acos(uv);
}

osg::Matrix getRotationMatrix(const osg::Vec3d& fromVector, const osg::Vec3d& toVector)
{
    const osg::Vec3d xAxis(1, 0, 0);
    const osg::Vec3d yAxis(0, 1, 0);
    const osg::Vec3d zAxis(0, 0, 1);

    //Task 7 - compute the rotation matrix around arbitrary axis
    
    //Compute the angle between input vectors - function angleBetweenVectors

    double angleBetweenInput = angleBetweenVectors(fromVector, toVector);

    //7a - compute the rotation axis using the cross product - operator ^
    
    auto rotationAxis = cross(fromVector, toVector);

    //7b - project rotation axis into XZ plane

    auto XZplane = projectOnPlane(rotationAxis, yAxis);

    //7c - compute the angle between rotation axis and XZ plane (projected axis)

    auto angleToXZplane = angleBetweenVectors(rotationAxis, XZplane);

    //7d - compute rotation around Z axis

    auto ZRotation = rotateAroundZ(angleToXZplane);
    auto reverseZRotation = rotateAroundZ(-angleToXZplane);

    //7e - compute angle between rotation and X axis and rotate corrently, hint - for Pi use M_PI

    auto angleToX = angleBetweenVectors(XZplane, xAxis);

    if (XZplane.z()<0)
    {
        angleToX = 2 * M_PI - angleToX;
    }

    //7f - compute the desired rotation


    //7g - compute and return the final rotation

    osg::Matrix result;
    
    result = ZRotation * rotateAroundY(angleToX) * rotateAroundX(angleBetweenInput) * rotateAroundY(-angleToX) * reverseZRotation;

    return result;
}
#else

osg::Matrix getScaleMatrix(const osg::Vec3d& scale)
{
    return osg::Matrix::scale(scale);
}

osg::Matrix getTranslationMatrix(const osg::Vec3d& translation)
{
    return osg::Matrix::translate(translation);
}

osg::Matrix getRotationMatrix(const osg::Vec3d& fromVector, const osg::Vec3d& toVector)
{
    osg::Quat q;
    q.makeRotate(fromVector, toVector);

    return osg::Matrix(q);
}

osg::Matrix rotateAroundX(double angle)
{
    return {};
}

osg::Matrix rotateAroundY(double angle)
{
    return {};
}

osg::Matrix rotateAroundZ(double angle)
{
    return {};
}

double angleBetweenVectors(osg::Vec3d u, osg::Vec3d v)
{
    return 0.0;
}
#endif