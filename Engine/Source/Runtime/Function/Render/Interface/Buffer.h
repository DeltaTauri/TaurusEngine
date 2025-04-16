#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Core/Macro.h"

namespace Taurus
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case Taurus::ShaderDataType::None:            return 0;
        case Taurus::ShaderDataType::Float:           return 4 * 1;
        case Taurus::ShaderDataType::Float2:          return 4 * 2;
        case Taurus::ShaderDataType::Float3:          return 4 * 3;
        case Taurus::ShaderDataType::Float4:          return 4 * 4;
        case Taurus::ShaderDataType::Mat3:            return 4 * 3 * 3;
        case Taurus::ShaderDataType::Mat4:            return 4 * 4 * 4;
        case Taurus::ShaderDataType::Int:             return 4;
        case Taurus::ShaderDataType::Int2:            return 4 * 2;
        case Taurus::ShaderDataType::Int3:            return 4 * 3;
        case Taurus::ShaderDataType::Int4:            return 4 * 4;
        case Taurus::ShaderDataType::Bool:            return 1;
        }
        TAURUS_ASSERT(false && "Unkonw ShaderType");
        return 0;
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        size_t Offset;

        BufferElement(ShaderDataType type, const std::string& name) :Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
        {
        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case Taurus::ShaderDataType::Float:         return 1;
            case Taurus::ShaderDataType::Float2:        return 2;
            case Taurus::ShaderDataType::Float3:        return 3;
            case Taurus::ShaderDataType::Float4:        return 4;
            case Taurus::ShaderDataType::Mat3:          return 3;
            case Taurus::ShaderDataType::Mat4:          return 4;
            case Taurus::ShaderDataType::Int:           return 1;
            case Taurus::ShaderDataType::Int2:          return 2;
            case Taurus::ShaderDataType::Int3:          return 3;
            case Taurus::ShaderDataType::Int4:          return 4;
            case Taurus::ShaderDataType::Bool:          return 1;
            }
            TAURUS_ASSERT(false && "Unkonw ShaderType");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> element):m_Elements(element)
        {
            CalculateOffsetsAndStride();
        }
        uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
            
        }
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;
        static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual uint32_t GetCount() const = 0;
        static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t size);
    };
}