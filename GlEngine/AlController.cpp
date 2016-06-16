#include "stdafx.h"
#include "AlController.h"
#include "AlControllerImpl.h"

namespace GlEngine
{
    AlController::AlController()
        : pimpl(new Impl::AlControllerImpl())
    {
    }
    AlController::~AlController()
    {
        if (pimpl != nullptr)
        {
            Shutdown();
            delete pimpl;
            pimpl = nullptr;
        }
    }

    AlController AlController::_instance;

    bool AlController::Initialize()
    {
        return pimpl->Initialize();
    }
    void AlController::Shutdown()
    {
        pimpl->Shutdown();
    }

    IAudioSource *AlController::CreateAudioSource()
    {
        return pimpl->CreateAudioSource();
    }
    void AlController::ReleaseAudioSource(IAudioSource *source)
    {
        pimpl->ReleaseAudioSource(source);
    }

    std::mutex &AlController::GetMutex()
    {
        return pimpl->GetMutex();
    }
}
