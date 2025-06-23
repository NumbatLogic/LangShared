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

	XmlFile::XmlFile() : XmlNode(NULL, NULL)
	{
		m_pDocument = NULL;
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

	void XmlFile::Cleanup()
	{
		if (m_pDocument)
		{
			delete m_pDocument;
		}
	}
}
