#pragma once

#include "../Vector/OwnedVector.hpp"
#include "../../InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class InternalString;
	template <class T>
	class OwnedVector;
}
#line 0 "../LangShared/Transpiled/Xml/XmlWriter.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Xml/XmlWriter.nll"
	class XmlWriter
	{
#line 5 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: InternalString* m_sOutput;
#line 6 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: int m_nIndentLevel;
#line 7 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: bool m_bCompactMode;
#line 8 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: bool m_bElementOpen;
#line 9 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: bool m_bElementHasContent;
#line 10 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: OwnedVector<InternalString*>* m_sElementStack;
#line 12 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: XmlWriter(bool bCompact);
#line 22 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: void StartElement(const char* sName);
#line 47 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: void EndElement();
#line 77 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: void SetAttribute(const char* sName, const char* sValue);
#line 91 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: void SetText(const char* sText);
#line 107 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: InternalString* GetOutput();
#line 112 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: void WriteIndent();
#line 120 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: void WriteEscapedText(const char* sText);
#line 153 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected: void WriteEscapedAttribute(const char* sValue);
#line 3 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public: virtual ~XmlWriter();
	};
}

