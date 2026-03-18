<?
	global $g_sTestArray;
	global $g_sTestNamespace;
	global $g_sTestArgVector;

	$g_sTestArray = array();
	$g_sTestNamespace = null;
	$g_sTestArgVector = "sArgVector";

	function Test_Add($sTest)
	{
		global $g_sTestArray;
		$g_sTestArray[] = $sTest;
	}

	function Test_SetFolder($sFolder)
	{
		global $g_sTestArray;
		$g_sTestArray = array();

		global $g_sTestNamespace;
		$g_sTestNamespace = null;
		global $g_sTestArgVector;
		$g_sTestArgVector = "sArgVector";

		$pDirectory = opendir($sFolder);
			while($sFile = readdir($pDirectory))
			{
				if ($sFile != "." && $sFile != ".." && !is_dir($sFolder . "/" . $sFile))
				{
					$pPathInfo = pathinfo($sFile);
					if ($pPathInfo['extension'] == "nll")// && $sFile != "Main.nll")
						Test_Add($pPathInfo['filename']);
				}
			}
		closedir($pDirectory);

		sort($g_sTestArray);
	}

	function Test_SetNamespace($sNamespace)
	{
		global $g_sTestNamespace;
		$g_sTestNamespace = $sNamespace;
	}

	function Test_SetArgVector($sArgVector)
	{
		global $g_sTestArgVector;
		$g_sTestArgVector = $sArgVector;
	}

	function Test_DisableArgVector()
	{
		global $g_sTestArgVector;
		$g_sTestArgVector = null;
	}

	function Test_Output($bNamespace = false)
	{
		global $g_sTestArray;
		global $g_sTestNamespace;
		global $g_sTestArgVector;

		for ($i = 0; $i < sizeof($g_sTestArray); $i++)
		{
			$sTest = $g_sTestArray[$i];

			$sClassName = "";
			if ($g_sTestNamespace != null)
				$sClassName = "$g_sTestNamespace::";
			if ($bNamespace)
				$sClassName .= "$sTest::Test";
			else
				$sClassName .= "$sTest";

			$sIndent = "\t";
			if ($g_sTestArgVector != null)
			{
				Output("\tif ($g_sTestArgVector.GetSize() == 0 || ExternalString::Equal($g_sTestArgVector.Get(0), \"$sTest\"))\n");
				Output("\t{\n");
				$sIndent = "\t\t";
			}

			Output("$sIndent" . "Console::Log(\"$sTest\");\n");
			Output("$sIndent" . "$sClassName::Run();\n");

			if ($g_sTestArgVector != null)
			{
				Output("\t}\n");
			}
		}
		Output("\n");
	}
?>