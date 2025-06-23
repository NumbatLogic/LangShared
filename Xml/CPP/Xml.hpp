#pragma once

#ifndef CLANG_PARSE
	#include "tinyxml2/tinyxml2.h"
#endif

namespace NumbatLogic { class BlobView; }

namespace NumbatLogic
{
	template <class T>
	class Vector;

	class XmlNode
	{
		public:
			XmlNode* GetFirstChildElement(const char* szName);
			XmlNode* GetNextSiblingElement(const char* szName);
			const char* GetValue();
			const char* GetText();
			const char* GetAttribute(const char* szName);

		protected:
			#ifndef CLANG_PARSE
				XmlNode(tinyxml2::XMLNode* pNode, XmlNode* pParent);
				virtual ~XmlNode();

				tinyxml2::XMLNode* m_pNode;
				XmlNode* m_pParent;
				Vector<XmlNode*>* m_pChildNodeVector;
			#endif
	};

	class XmlFile : public XmlNode
	{
		public:
			XmlFile();
			~XmlFile();

			bool Load(BlobView* pBlobView);
			bool Save(BlobView* pBlobView);

		protected:
			#ifndef CLANG_PARSE
				void Cleanup();

				tinyxml2::XMLDocument* m_pDocument;
			#endif
	};
}
