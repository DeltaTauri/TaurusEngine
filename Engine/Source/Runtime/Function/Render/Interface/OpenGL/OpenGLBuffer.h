#pragma once
#include "Function/Render/Interface/Buffer.h"

namespace Taurus
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* data, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
        virtual const BufferLayout& GetLayout() const override { return m_Layout; };
    private:
        uint32_t m_VBO;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* data, uint32_t size);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual uint32_t GetCount() const override { return m_Count; };
    private:
        uint32_t m_IBO;
        uint32_t m_Count;
    };
}