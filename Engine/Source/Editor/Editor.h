#pragma once

#include <memory>

namespace Taurus
{
    class TaurusEngine;

    class TaurusEditor
    {
    public:
        TaurusEditor();
        virtual ~TaurusEditor();

        void Initialize(TaurusEngine* engine_runtime);
        void ShutDown();

        void Run();

    protected:
        TaurusEngine* m_engine_runtime{ nullptr };
    };
}