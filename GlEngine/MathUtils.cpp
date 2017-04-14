#include "stdafx.h"
#include "MathUtils.h"

/*
triangle - AABB collision test
copied with modifications from http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/tribox3.txt
*/

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

bool planeBoxOverlap(Vector<3> normal, Vector<3> vert, Vector<3> maxbox)
{
    int q;
    float vmin[3], vmax[3], v;
    for (q = 0; q <= 2; q++)
    {
        v = vert[q];
        if (normal[q]>0.0f)
        {
            vmin[q] = -maxbox[q] - v;
            vmax[q] = maxbox[q] - v;
        }
        else
        {
            vmin[q] = maxbox[q] - v;
            vmax[q] = -maxbox[q] - v;
        }
    }
    if (normal.Dot({ vmin[0], vmin[1], vmin[2] }) > 0.0f) return false;
    if (normal.Dot({ vmax[0], vmax[1], vmax[2] }) >= 0.0f) return true;
    return false;
}

/*======================== X-tests ========================*/
#define AXISTEST_X01(a, b, fa, fb) \
    p0 = a*v0[1] - b*v0[2]; \
    p2 = a*v2[1] - b*v2[2]; \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[1] + fb * boxhalfsize[2]; \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_X2(a, b, fa, fb) \
    p0 = a*v0[1] - b*v0[2]; \
    p1 = a*v1[1] - b*v1[2]; \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[1] + fb * boxhalfsize[2]; \
    if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
#define AXISTEST_Y02(a, b, fa, fb) \
    p0 = -a*v0[0] + b*v0[2]; \
    p2 = -a*v2[0] + b*v2[2]; \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[0] + fb * boxhalfsize[2]; \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Y1(a, b, fa, fb) \
    p0 = -a*v0[0] + b*v0[2]; \
    p1 = -a*v1[0] + b*v1[2]; \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[0] + fb * boxhalfsize[2]; \
    if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/
#define AXISTEST_Z12(a, b, fa, fb) \
    p1 = a*v1[0] - b*v1[1]; \
    p2 = a*v2[0] - b*v2[1]; \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
    rad = fa * boxhalfsize[0] + fb * boxhalfsize[1]; \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Z0(a, b, fa, fb) \
    p0 = a*v0[0] - b*v0[1]; \
    p1 = a*v1[0] - b*v1[1]; \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[0] + fb * boxhalfsize[1]; \
    if(min>rad || max<-rad) return false;

bool triBoxOverlap(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> boxcenter, Vector<3> boxhalfsize)
{
    /*    use separating axis theorem to test overlap between triangle and box */
    /*    need to test for overlap in these directions: */
    /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
    /*       we do not even need to test these) */
    /*    2) normal of the triangle */
    /*    3) crossproduct(edge from tri, {x,y,z}-directin) */
    /*       this gives 3x3=9 more tests */
    //   float axis[3];
    float min, max, p0, p1, p2, rad, fex, fey, fez;        // -NJMP- "d" local variable removed

                                                           /* This is the fastest branch on Sun */
                                                           /* move everything so that the boxcenter is in (0,0,0) */

    auto v0 = t1 - boxcenter;
    auto v1 = t2 - boxcenter;
    auto v2 = t3 - boxcenter;

    /* compute triangle edges */
    auto e0 = v1 - v0;
    auto e1 = v2 - v1;
    auto e2 = v0 - v2;

    /* Bullet 3:  */
    /*  test the 9 tests first (this was faster) */
    fex = fabsf(e0[0]);
    fey = fabsf(e0[1]);
    fez = fabsf(e0[2]);
    AXISTEST_X01(e0[2], e0[1], fez, fey);
    AXISTEST_Y02(e0[2], e0[0], fez, fex);
    AXISTEST_Z12(e0[1], e0[0], fey, fex);

    fex = fabsf(e1[0]);
    fey = fabsf(e1[1]);
    fez = fabsf(e1[2]);
    AXISTEST_X01(e1[2], e1[1], fez, fey);
    AXISTEST_Y02(e1[2], e1[0], fez, fex);
    AXISTEST_Z0(e1[1], e1[0], fey, fex);

    fex = fabsf(e2[0]);
    fey = fabsf(e2[1]);
    fez = fabsf(e2[2]);
    AXISTEST_X2(e2[2], e2[1], fez, fey);
    AXISTEST_Y1(e2[2], e2[0], fez, fex);
    AXISTEST_Z12(e2[1], e2[0], fey, fex);

    /* Bullet 1: */
    /*  first test overlap in the {x,y,z}-directions */
    /*  find min, max of the triangle each direction, and test for overlap in */
    /*  that direction -- this is equivalent to testing a minimal AABB around */
    /*  the triangle against the AABB */

    /* test in X-direction */
    FINDMINMAX(v0[0], v1[0], v2[0], min, max);
    if (min>boxhalfsize[0] || max < -boxhalfsize[0]) return false;

    /* test in Y-direction */
    FINDMINMAX(v0[1], v1[1], v2[1], min, max);
    if (min>boxhalfsize[1] || max < -boxhalfsize[1]) return false;

    /* test in Z-direction */
    FINDMINMAX(v0[2], v1[2], v2[2], min, max);
    if (min>boxhalfsize[2] || max < -boxhalfsize[2]) return false;

    /* Bullet 2: */
    /*  test if the box intersects the plane of the triangle */
    /*  compute plane equation of triangle: normal*x+d=0 */

    auto normal = e0.Cross(e1);
    // -NJMP- (line removed here)
    if (!planeBoxOverlap(normal, v0, boxhalfsize)) return false;    // -NJMP-

    return true;   /* box and triangle overlaps */}

#undef FINDMINMAX
#undef AXISTEST_X01
#undef AXISTEST_X2
#undef AXISTEST_Y02
#undef AXISTEST_Y1
#undef AXISTEST_Z12
#undef AXISTEST_Z0

namespace GlEngine
{
    namespace Util
    {
        constexpr float radToDeg(const float rad)
        {
            return (float)(rad / PI * 180);
        }
        constexpr float degToRad(const float deg)
        {
            return (float)(deg * PI / 180);
        }

        constexpr double radToDeg_d(const double rad)
        {
            return rad / PI * 180;
        }
        constexpr double degToRad_d(const double deg)
        {
            return deg * PI / 180;
        }

        // Moller-Trumbore ray-triangle intersection algorithm
        bool triangleRayIntersection(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> rayOrigin, Vector<3> rayDirection, float* outDistance)
        {
            static const float epsilon = 0.000001f;

            auto edge1 = t2 - t1;
            auto edge2 = t3 - t1;

            auto P = rayDirection.Cross(edge2);

            float det = edge1.Dot(P);
            if (det < epsilon && det > -epsilon) // ray is parallel to triangle
                return false;

            float invDet = 1.f / det;
    
            auto T = rayOrigin - t1;
            float u = T.Dot(P) * invDet;

            if (u < 0.f || u > 1.f) // no intersection
                return false;

            auto Q = T.Cross(edge1);
            float v = rayDirection.Dot(Q) * invDet;

            if (v < 0.f || u + v > 1.f) // no intersection
                return false;

            float t = edge2.Dot(Q) * invDet;
            if (t > epsilon)
            {
                if (outDistance != nullptr)
                    *outDistance = t;
                return true;
            }

            return false; // wrong side
        }

        bool triangleAABBIntersection(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> topLeftBack, Vector<3> size)
        {
            auto halfSize = size / 2.0f;
            return triBoxOverlap(t1, t2, t3, topLeftBack + halfSize, halfSize);
        }

        bool pointInTriangle2d(Vector<2> point, Vector<2> t1, Vector<2> t2, Vector<2> t3)
        {
            float A = 1 / 2 * (-t2[1] * t3[0] + t1[1] * (-t2[0] + t3[0]) + t1[0] * (t2[1] - t3[1]) + t2[0] * t3[1]);
            int sign = A < 0 ? -1 : 1;
            float s = (t1[1] * t3[0] - t1[0] * t3[1] + (t3[1] - t1[1]) * point[0] + (t1[0] - t3[0]) * point[1]) * sign;
            float t = (t1[0] * t2[1] - t1[1] * t2[0] + (t1[1] - t2[1]) * point[0] + (t2[0] - t1[0]) * point[1]) * sign;

            return s > 0 && t > 0 && (s + t) < 2 * A * sign;
        }
    }
}

float operator "" rad(long double angle)
{
    return static_cast<float>(angle);
}
float operator "" deg(unsigned long long angle)
{
    return GlEngine::Util::degToRad((float)angle);
}
float operator "" deg(long double angle)
{
    return GlEngine::Util::degToRad((float)angle);
}

double operator "" rad_d(long double angle)
{
    return static_cast<double>(angle);
}
double operator "" deg_d(unsigned long long angle)
{
    return GlEngine::Util::degToRad_d((double)angle);
}
double operator "" deg_d(long double angle)
{
    return GlEngine::Util::degToRad_d((double)angle);
}