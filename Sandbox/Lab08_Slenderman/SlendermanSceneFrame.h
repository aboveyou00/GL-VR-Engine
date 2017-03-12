
#include "Subroutine.h"
#include "Frame.h"
#include "ComponentArray.h"
#include <map>

class SlendermanStaticSceneFrame;

class SlendermanSceneFrame : public GlEngine::Frame
{
public:
    SlendermanSceneFrame();
    ~SlendermanSceneFrame();

    friend class SlendermanStaticSceneFrame;

    virtual bool Initialize() override;

private:
    float static_amount;
};
