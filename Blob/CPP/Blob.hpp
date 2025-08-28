#pragma once

namespace NumbatLogic
{
	class InternalString;
	class BlobView;

	class Blob
	{
		public:
			Blob(bool bAutoResize);
			~Blob();

			bool Load(const char* szFileName);
			bool Save(const char* szFileName);

			void Resize(int nSize, bool bAutoResize);
			int GetSize();

			unsigned int GetMsoCrc32();

			BlobView* GetBlobView();

			bool Equal(Blob* pOther);

			// to hide
			void PackData(unsigned char* pData, int nOffset, int nSize);
			void UnpackData(unsigned char* pData, int nOffset, int nSize);
			unsigned char* GetData();

			Blob* Clone();

		protected:
			friend class BlobView;

			static const int DEFAULT_SIZE = 1024 * 32;

			int m_nBufferSize;
			unsigned char* m_pBuffer;
			int m_nSize;
			bool m_bAutoResize;
			BlobView* m_pBlobView;
	};

	class BlobView
	{
		public:
			BlobView(Blob* pBlob, int nStart, int nEnd);
			~BlobView();

			unsigned char GetChecksum();

			int GetSize();

			void PackBool(bool b);

			void PackUint8(unsigned char n);
			void PackUint16(unsigned short n);
			void PackUint32(unsigned int n);

			void PackInt8(signed char n);
			void PackInt16(signed short n);
			void PackInt32(signed int n);

			void PackDouble(double n);

			void PackExternalString(const char* sxString);
			void PackInternalString(InternalString* sString);
			void PackBlob(Blob* pBlob);

			bool UnpackBool();

			unsigned char UnpackUint8();
			unsigned short UnpackUint16();
			unsigned int UnpackUint32();

			signed char UnpackInt8();
			signed short UnpackInt16();
			signed int UnpackInt32();

			double UnpackDouble();

			bool UnpackInternalString(InternalString* sString);
			bool UnpackBlob(Blob* pBlob);

			signed int UnpackInt32At(int nOffset);

			int GetStart();
			int GetEnd();

			void SetEnd(int nEnd);

			int GetOffset();
			void SetOffset(int nOffset);

			void Pack(BlobView* pBlobView, int nSize);
			void PackAt(int nOffset, BlobView* pBlobView, int nSize);

			void Unpack(BlobView* pBlobView, int nSize);
			void UnpackAt(int nOffset, BlobView* pBlobView, int nSize);

			Blob* GetBlob();

			//protected:
			// hax for now

			void PackData(unsigned char* pData, int nSize);
			void UnpackData(unsigned char* pData, int nSize);

			void PackDataAt(int nOffset, unsigned char* pData, int nSize);
			void UnpackDataAt(int nOffset, unsigned char* pData, int nSize);

		protected:
			int m_nStart;
			int m_nEnd;
			int m_nOffset;

			Blob* m_pBlob;
	};
}
