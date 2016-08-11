#pragma once

#include "VboGraphicsObject.h"
#include "fbxsdk.h"

namespace GlEngine
{
    namespace Impl
    {
        class FbxSectionGraphicsObject : public VboGraphicsObject
        {
        public:
            FbxSectionGraphicsObject(fbxsdk::FbxMesh *fbxMesh);
            ~FbxSectionGraphicsObject();

            bool Initialize() override;
            void Shutdown() override;

        private:
            fbxsdk::FbxMesh *mesh;
            std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> *glVertices;

            int findOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        };
    }
}
