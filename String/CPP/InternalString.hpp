#pragma once

#include <cstddef>
#include <string.h>	// for NULL

namespace NumbatLogic
{
	class BlobView;

	class InternalString
	{
		public:
			InternalString(const char* sxString);
			~InternalString();

			InternalString* CreateClone();

			void Set(const char* sxString);
			const char* GetExternalString() const;

			void Append(const char* sxString);
			void AppendChar(unsigned short nChar);
			void AppendString(const char* sxString);
			void AppendStringData(unsigned char* pData, int nLength);

			void AppendInt(int nInt);
			void AppendUnsignedInt(unsigned int nUint32);
			void AppendUint32(unsigned int nUint32);
			void AppendDouble(double fDouble);

			void PrependChar(unsigned short nChar);
			void PrependString(const char* sxString);

			void SubStr(int nStart, int nLength);
			void CropFront(int nLength);

			//void CropBack(int nLength);

			int GetLength();
			unsigned short GetChar(int nIndex);

			void BlobWriteUtf8(BlobView* pBlobView, bool bZeroTerminator);
			void BlobWrite16Bit(BlobView* pBlobView, bool bZeroTerminator);

			bool IsAscii();

			bool IsEqual(const char* sxCompare);
			bool StartsWith(const char* sxString);
			bool EndsWith(const char* sxString);

			double ParseDouble();
			unsigned int ParseHex();

			int FindChar(unsigned short nChar);

			void Replace(const char* sxFind, const char* sxReplace);

		protected:
			char* m_sxBuffer;
			int m_nBufferSize;

			int m_nByteLength;
			int m_nCharLength;

			void Resize(int nSize);

			static int GetCharSize(unsigned short nChar);
			static int GetUtf8CharSize(unsigned char cLeadChar);
			static bool GetUtf8Length(const char* sxString, int* pCharLength, int* pByteLength);

			static unsigned short DecodeChar(unsigned char* pUtf8Char);
			static int EncodeChar(unsigned short nChar, unsigned char* pBuffer);
	};
}