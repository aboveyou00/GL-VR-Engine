#pragma once

namespace GlEngine
{
    enum class ImageComponentAlignment
    {
        Begin,
        Middle,
        End
    };

    typedef struct {
        ImageComponentAlignment horiz, vert;
    } ImageAlignment;

    namespace Util
    {
        Matrix<4, 4> GetAlignmentMatrix(ImageAlignment align);
        float GetComponentAlignment(ImageComponentAlignment align);
    }
}
