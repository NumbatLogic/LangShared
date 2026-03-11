#line 1 "../LangShared/Transpiled/Xml/XmlWriter.nll"
namespace NumbatLogic
{
#line 3 "../LangShared/Transpiled/Xml/XmlWriter.nll"
	class XmlWriter
	{
#line 5 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected InternalString m_sOutput;
#line 6 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected int m_nIndentLevel;
#line 7 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected bool m_bCompactMode;
#line 8 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected bool m_bElementOpen;
#line 9 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected bool m_bElementHasContent;
#line 10 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected OwnedVector<InternalString> m_sElementStack;
#line 12 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public XmlWriter(bool bCompact)
		{
#line 14 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput = new InternalString("");
#line 15 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_nIndentLevel = 0;
#line 16 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bCompactMode = bCompact;
#line 17 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementOpen = false;
#line 18 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementHasContent = false;
#line 19 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sElementStack = new OwnedVector<InternalString>();
		}

#line 22 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public void StartElement(string sName)
		{
#line 24 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(sName != null);
#line 25 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(!ExternalString.Equal(sName, ""));
#line 27 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			if (m_bElementOpen)
			{
#line 29 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString(">");
#line 30 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_bElementOpen = false;
			}
#line 33 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			if (!m_bCompactMode && m_nIndentLevel > 0)
			{
#line 35 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString("\n");
#line 36 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				WriteIndent();
			}
#line 39 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString("<");
#line 40 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString(sName);
#line 41 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementOpen = true;
#line 42 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementHasContent = false;
#line 43 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_nIndentLevel++;
#line 44 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sElementStack.PushBack(new InternalString(sName));
		}

#line 47 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public void EndElement()
		{
#line 49 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(m_nIndentLevel > 0);
#line 50 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(m_sElementStack.GetSize() > 0);
#line 52 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_nIndentLevel--;
#line 54 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			if (m_bElementOpen)
			{
#line 56 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString(" />");
#line 57 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_bElementOpen = false;
#line 58 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sElementStack.PopBack();
			}
			else
			{
#line 62 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				if (!m_bCompactMode && !m_bElementHasContent)
				{
#line 64 "../LangShared/Transpiled/Xml/XmlWriter.nll"
					m_sOutput.AppendString("\n");
#line 65 "../LangShared/Transpiled/Xml/XmlWriter.nll"
					WriteIndent();
				}
#line 68 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				InternalString sElementName = m_sElementStack.PopBack();
#line 69 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString("</");
#line 70 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString(sElementName.GetExternalString());
#line 71 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString(">");
			}
#line 74 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementHasContent = false;
		}

#line 77 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public void SetAttribute(string sName, string sValue)
		{
#line 79 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(sName != null);
#line 80 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(!ExternalString.Equal(sName, ""));
#line 81 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(m_bElementOpen);
#line 82 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(sValue != null);
#line 84 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString(" ");
#line 85 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString(sName);
#line 86 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString("=\"");
#line 87 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			WriteEscapedAttribute(sValue);
#line 88 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_sOutput.AppendString("\"");
		}

#line 91 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public void SetText(string sText)
		{
#line 93 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(sText != null);
#line 94 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(!ExternalString.Equal(sText, ""));
#line 95 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			Assert.Plz(!m_bElementHasContent);
#line 97 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			if (m_bElementOpen)
			{
#line 99 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString(">");
#line 100 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_bElementOpen = false;
			}
#line 103 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			m_bElementHasContent = true;
#line 104 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			WriteEscapedText(sText);
		}

#line 107 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		public InternalString GetOutput()
		{
#line 109 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			return m_sOutput;
		}

#line 112 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected void WriteIndent()
		{
#line 114 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			for (int i = 0; i < m_nIndentLevel; i++)
			{
#line 116 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				m_sOutput.AppendString("    ");
			}
		}

#line 120 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected void WriteEscapedText(string sText)
		{
#line 122 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			InternalString sTemp = new InternalString(sText);
#line 124 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			for (int i = 0; i < sTemp.GetLength(); i++)
			{
#line 126 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				char c = sTemp.GetChar(i);
#line 127 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				switch (c)
				{
					case '<':
					{
#line 131 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&lt;");
#line 132 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '>':
					{
#line 136 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&gt;");
#line 137 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '&':
					{
#line 141 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&amp;");
#line 142 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					default:
					{
#line 146 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendChar(c);
#line 147 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

				}
			}
		}

#line 153 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		protected void WriteEscapedAttribute(string sValue)
		{
#line 155 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			InternalString sTemp = new InternalString(sValue);
#line 157 "../LangShared/Transpiled/Xml/XmlWriter.nll"
			for (int i = 0; i < sTemp.GetLength(); i++)
			{
#line 159 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				char c = sTemp.GetChar(i);
#line 160 "../LangShared/Transpiled/Xml/XmlWriter.nll"
				switch (c)
				{
					case '<':
					{
#line 164 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&lt;");
#line 165 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '>':
					{
#line 169 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&gt;");
#line 170 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '&':
					{
#line 174 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&amp;");
#line 175 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '"':
					{
#line 179 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&quot;");
#line 180 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					case '\'':
					{
#line 184 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendString("&apos;");
#line 185 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

					default:
					{
#line 189 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						m_sOutput.AppendChar(c);
#line 190 "../LangShared/Transpiled/Xml/XmlWriter.nll"
						break;
					}

				}
			}
		}

#line 3 "../LangShared/Transpiled/Xml/XmlWriter.nll"
		~XmlWriter()
		{
		}

	}
}

