#pragma once

#include "../Platform/Typedef.hpp"
#include <cstring>

namespace Amalgamation {

    template<class Type>
    class Optional{

        Type* m_Data;
        bool m_HasData;

    public:

        Optional(const Type& Data) : m_Data(new Type(Data)), m_HasData(true) {}
        template<class... TArgs>
        Optional(TArgs&&... Args) : m_Data(new Type(std::forward<TArgs>(Args)...)), m_HasData(true) {}
        Optional() : m_Data(nullptr), m_HasData(false) {}
        ~Optional() { SafeDelete(m_Data); }

        Optional(const Optional& Other) : m_HasData(Other.m_HasData) {
            SafeDelete(m_Data);
            m_Data = new Type((*Other.m_Data));
        }

        bool HasData() const{
            return m_HasData;
        }

        Type& Data() {
            return *m_Data;
        }

        Type& operator*(){
            return *m_Data;
        }

        Type* operator->(){
            return m_Data;
        }

        constexpr explicit operator bool() const noexcept{
            return m_HasData;
        }

        void Purge(){
            SafeDelete(m_Data);
            m_HasData = false;
        }

    };

}
