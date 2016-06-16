#include "stdafx.h"
#include "AlControllerImpl.h"

namespace GlEngine
{
    namespace Impl
    {
        AlControllerImpl::AlControllerImpl()
        {
        }
        AlControllerImpl::~AlControllerImpl()
        {
        }

        bool AlControllerImpl::Initialize()
        {
            return true;
        }
        void AlControllerImpl::Shutdown()
        {
        }

        IAudioSource *AlControllerImpl::CreateAudioSource()
        {
            return nullptr;
        }
        void AlControllerImpl::ReleaseAudioSource(IAudioSource *source)
        {
            source;
        }
    }
}
