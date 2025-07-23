#include "../../Assert/CPP/Assert.hpp"
#include "../../InternalString/CPP/InternalString.hpp"
#include "../../Vector/CPP/Vector.hpp"
#include "../../Blob/CPP/Blob.hpp"
#include "Xml.hpp"

namespace NumbatLogic
{
	XmlNode::XmlNode(tinyxml2::XMLNode* pNode, XmlNode* pParent)
	{
		m_pNode = pNode;
		m_pParent = pParent;
		m_pChildNodeVector = new Vector<XmlNode*>();
	}

	XmlNode::~XmlNode()
	{
		while (m_pChildNodeVector->GetSize())
			delete m_pChildNodeVector->PopBack();
		delete m_pChildNodeVector;
	}

	XmlNode* XmlNode::GetFirstChildElement(const char* szName)
	{
		tinyxml2::XMLElement* pTemp = m_pNode->FirstChildElement(szName);
		if (!pTemp)
			return NULL;

		XmlNode* pChildNode = new XmlNode(pTemp, this);
		m_pChildNodeVector->PushBack(pChildNode);
		return pChildNode;
	}

	// super fucking hax
	XmlNode* XmlNode::GetNextSiblingElement(const char* szName)
	{
		tinyxml2::XMLElement* pTemp = m_pNode->NextSiblingElement(szName);
		if (!pTemp)
			return NULL;

		XmlNode* pSiblingNode = new XmlNode(pTemp, m_pParent);
		m_pParent->m_pChildNodeVector->PushBack(pSiblingNode);
		return pSiblingNode;
	}

	const char* XmlNode::GetValue()
	{
		return m_pNode->Value();
	}

	const char* XmlNode::GetText()
	{
		tinyxml2::XMLElement* pElement = m_pNode->ToElement();
		if (pElement)
			return pElement->GetText();
		return NULL;
	}

	const char* XmlNode::GetAttribute(const char* szName)
	{
		tinyxml2::XMLElement* pElement = m_pNode->ToElement();
		if (pElement)
			return pElement->Attribute(szName);
		return NULL;
	}

	void XmlNode::SetAttribute(const char* szName, const char* szValue)
	{
		tinyxml2::XMLElement* pElement = m_pNode ? m_pNode->ToElement() : NULL;
		if (pElement)
		{
			pElement->SetAttribute(szName, szValue);
		}
	}

	void XmlNode::SetText(const char* szText)
	{
		tinyxml2::XMLElement* pElement = m_pNode ? m_pNode->ToElement() : NULL;
		if (pElement)
		{
			pElement->SetText(szText);
		}
	}

	void XmlNode::AppendChild(XmlNode* pChild)
	{
		if (pChild && pChild->m_pNode && m_pNode)
		{
			m_pNode->InsertEndChild(pChild->m_pNode);
		}
	}

	XmlFile::XmlFile() : XmlNode(NULL, NULL)
	{
		m_pDocument = new tinyxml2::XMLDocument();
		m_pNode = m_pDocument;
	}

	XmlFile::~XmlFile()
	{
		Cleanup();
	}

	bool XmlFile::Load(BlobView* pBlobView)
	{
		const char* szRawXml = (const char*)(pBlobView->GetBlob()->GetData() + pBlobView->GetStart() + pBlobView->GetOffset());
		size_t nSize = (size_t)(pBlobView->GetSize() - pBlobView->GetOffset());
		tinyxml2::XMLError error;

		Cleanup();

		m_pDocument = new tinyxml2::XMLDocument();
		error = m_pDocument->Parse(szRawXml, nSize);
		if (error != tinyxml2::XML_SUCCESS)
		{
			Cleanup();
			return false;
		}

		m_pNode = m_pDocument;

		return true;
	}

	bool XmlFile::Save(BlobView* pBlobView)
	{
		if (!m_pDocument)
			return false;

		// Create a memory buffer to hold the XML
		tinyxml2::XMLPrinter printer;
		m_pDocument->Print(&printer);
		
		const char* szXml = printer.CStr();
		int nSize = (int)strlen(szXml);
		
		// Ensure the blob has enough space
		if (pBlobView->GetBlob()->GetSize() < pBlobView->GetStart() + nSize)
		{
			pBlobView->GetBlob()->Resize(pBlobView->GetStart() + nSize, true);
		}
		
		// Copy the XML data to the blob
		memcpy(pBlobView->GetBlob()->GetData() + pBlobView->GetStart(), szXml, nSize);
		
		return true;
	}

	bool XmlFile::SaveToString(InternalString* sOut)
	{
		if (!m_pDocument)
			return false;

		tinyxml2::XMLPrinter printer;
		m_pDocument->Print(&printer);
		const char* szXml = printer.CStr();
		if (!szXml)
			return false;
		sOut->AppendString(szXml);
		return true;
	}

	void XmlFile::Cleanup()
	{
		if (m_pDocument)
		{
			delete m_pDocument;
			m_pDocument = NULL;
			m_pNode = NULL;
		}
	}

	XmlNode* XmlFile::CreateElement(const char* szName)
	{
		if (!m_pDocument)
			return NULL;

		tinyxml2::XMLElement* pNewElement = m_pDocument->NewElement(szName);
		if (!pNewElement)
			return NULL;

		XmlNode* pNewNode = new XmlNode(pNewElement, this);
		m_pChildNodeVector->PushBack(pNewNode);
		return pNewNode;
	}
}
