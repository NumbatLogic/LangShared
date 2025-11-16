#pragma once

namespace NumbatLogic
{
	class InternalString;

	class gsBlob
	{
		public:
			gsBlob();
			~gsBlob();

			bool Load(const char* szFileName);
			bool Save(const char* szFileName);
	
			bool IsEqual(gsBlob* pOther);
			unsigned char GetChecksum();
			gsBlob* Clone();
			
			int GetSize();
			int GetOffset();
			void SetOffset(int nOffset);
			void Reset();

			// Pack
			void PackBool(bool val);

			void PackInt8(signed char val);
			void PackInt16(signed short val);
			void PackInt32(signed int val);
			
			void PackUint8(unsigned char val);
			void PackUint16(unsigned short val);
			void PackUint32(unsigned int val);
			void PackFloat(float val);
			void PackDouble(double val);

			void PackExternalString(const char* sxString);
			void PackInternalString(InternalString* sString);
			void PackBlob(gsBlob* pBlob);

			// Unpack
			bool UnpackBool(bool& val);

			bool UnpackInt8(signed char& val);
			bool UnpackInt16(signed short& val);
			bool UnpackInt32(signed int& val);

			bool UnpackUint8(unsigned char& val);
			bool UnpackUint16(unsigned short& val);
			bool UnpackUint32(unsigned int& val);
			bool UnpackFloat(float& val);
			bool UnpackDouble(double& val);

			bool UnpackInternalString(InternalString* sString);
			bool UnpackBlob(gsBlob* pBlob);

		// sekrit:
			bool Resize(int nSize);
			bool PackData(const unsigned char* pData, int nSize);
			bool UnpackData(unsigned char* pData, int nSize);
			unsigned char* GetData();

		protected:
			static const int DEFAULT_SIZE = 64;

			int m_nBufferSize;
			unsigned char* m_pBuffer;
			int m_nSize;
			int m_nOffset;
	};
}
