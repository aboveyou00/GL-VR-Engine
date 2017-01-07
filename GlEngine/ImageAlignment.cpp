#include "stdafx.h"
#include "ImageAlignment.h"

namespace GlEngine
{
    namespace Util
    {
        Matrix<4, 4> GetAlignmentMatrix(ImageAlignment align)
        {
            return Matrix<4, 4>::TranslateMatrix({
                GetComponentAlignment(align.horiz),
                GetComponentAlignment(align.vert)
            });
        }
        float GetComponentAlignment(ImageComponentAlignment align)
        {
            switch (align)
            {
            case GlEngine::ImageComponentAlignment::Begin:
                return 0.f;
            case GlEngine::ImageComponentAlignment::Middle:
                return -.5f;
            case GlEngine::ImageComponentAlignment::End:
                return -1.f;

            default:
                assert(false);
                return 0;
            }
        }
    }
}
