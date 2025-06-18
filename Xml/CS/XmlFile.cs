namespace NumbatLogic
{
    class XmlFile : XmlNode
    {
        public XmlFile() : base(null)
        {
        }

        public bool Load(BlobView pBlobView)
        {
            try
            {
                System.Xml.XmlDocument document = new System.Xml.XmlDocument();
                document.Load(pBlobView.CreateStream());
                m_pNode = document;
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }
    }
}