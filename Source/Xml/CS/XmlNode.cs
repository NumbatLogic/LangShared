namespace NumbatLogic
{
    public class XmlNode
    {
        protected System.Xml.XmlNode m_pNode;

        internal XmlNode(System.Xml.XmlNode pNode)
        {
            m_pNode = pNode;
        }

        public XmlNode GetFirstChildElement(string szName)
        {
            if (m_pNode.ChildNodes.Count > 0)
            {
                if (szName == null)
                    return new XmlNode(m_pNode.ChildNodes[0]);

                for (int i = 0; i < m_pNode.ChildNodes.Count; i++)
                {
                    System.Xml.XmlNode pNode = m_pNode.ChildNodes[i];
                    if (pNode.Name.Equals(szName))
                        return new XmlNode(pNode);
                }
            }
            return null;
        }

        public XmlNode GetNextSiblingElement(string szName)
        {
            if (m_pNode.NextSibling != null)
                return new XmlNode(m_pNode.NextSibling);
            return null;
        }

        public string GetValue()
        {
            return m_pNode.Name;
        }

        public string GetText()
        {
            return m_pNode.InnerText;
        }

        public string GetAttribute(string szName)
        {
            for (int i = 0; i < m_pNode.Attributes.Count; i++)
                if (m_pNode.Attributes[i].Name.Equals(szName))
                    return m_pNode.Attributes[i].Value;
            return null;
        }

        public void SetAttribute(string szName, string szValue)
        {
            if (m_pNode is System.Xml.XmlElement element)
            {
                element.SetAttribute(szName, szValue);
            }
        }

        public void SetText(string szText)
        {
            if (m_pNode is System.Xml.XmlElement element)
            {
                element.InnerText = szText;
            }
        }

        public void AppendChild(XmlNode pChild)
        {
            if (pChild != null && pChild.m_pNode != null)
            {
                m_pNode.AppendChild(pChild.m_pNode);
            }
        }
    }
}