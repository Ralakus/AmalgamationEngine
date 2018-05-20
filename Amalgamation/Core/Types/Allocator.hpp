#pragma once

#include "../Platform/Typedef.hpp"
#include <cstring>

namespace Amalgamation{

    class Allocator{

        friend class Array;

        Byte* m_Data;
        size_t m_Size;

    public:

        Allocator() : m_Data(nullptr), m_Size(0) {}
        Allocator(size_t Bytes) : m_Data(new Byte[Bytes]), m_Size(Bytes) {}
        ~Allocator() { SafeDeleteArr(m_Data); }

        void Resize(size_t Bytes){
            if(Bytes < 1){
                throw Error("Tried to allocate less than one byte!");
            }
            else{
                Byte* NewData = new Byte[Bytes];
                m_Size = Bytes;
                memcpy(NewData, m_Data, sizeof(Byte) * Bytes);
                SafeDeleteArr(m_Data);
                m_Data = NewData;
            }
        }

        void Allocate(size_t Bytes){
            this->Resize(m_Size + Bytes);
        }

        void Deallocate(size_t Bytes){
            this->Resize(m_Size - Bytes);
        }

        /*WARNING UNSAFE!*/
        template<class Type>
        Type* GetDataAs(){
            if(sizeof(Type) > m_Size){
                throw Error("Not enough data allocated to cast to type!");
            }
            return reinterpret_cast<Type*>(m_Data);
        }

        template<class Type>
        void AddData(Type* Data, size_t ByteCount, size_t ByteOffset = 0){
            if(ByteCount > (m_Size - ByteOffset)){
                    throw Error("Need to fix the resizing in this function, Sorry!");
                //this->Resize(ByteCount);
            }
            memcpy(m_Data + ByteOffset, Data, ByteCount);
        }

        size_t GetLastEmptyIndex(){
            for(size_t i = 0; i < m_Size; i++){
                if(m_Data[i] == 0){
                    return i;
                }
            }
            return -1;
        }

        Byte* GetLastEmpty(){
            for(Byte* i = m_Data, *end = &m_Data[m_Size]; i < end; i++){
                if(i == 0){
                    return i;
                }
            }
            return nullptr;
        }

        Byte* GetDataPtr(){
            return m_Data;
        }

    };

}
