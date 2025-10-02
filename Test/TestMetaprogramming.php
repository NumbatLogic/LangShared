<?
	global $g_sTestArray;
	$g_sTestArray = array();

	function Test_Add($sTest)
	{
		global $g_sTestArray;
		$g_sTestArray[] = $sTest;
	}

	function Test_SetFolder($sFolder)
	{
		global $g_sTestArray;
		$g_sTestArray = array();

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

	function Test_Output($bNamespace = false)
	{	
		global $g_sTestArray;

		for ($i = 0; $i < sizeof($g_sTestArray); $i++)
		{
			$sTest = $g_sTestArray[$i];
			Output("\tConsole::Log(\"$sTest\");\n");
			if ($bNamespace)
				Output("\t$sTest::Test::Run();\n");
			else
				Output("\t$sTest::Run();\n");
		}
		Output("\n");
	}
?>