<?php
	class LangShared_Config extends Project_Config
	{	
		public function __construct($sAction, $sPackageList)
		{
			parent::__construct($sAction);

			$sAllowedDirectoryArray = file($sPackageList, FILE_IGNORE_NEW_LINES);
			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.hpp|\.cpp/",  $sAllowedDirectoryArray);
			// also transpiled folder?
		}

		public function GetName() { return "LangShared"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			$sArray = array(
				//"../Package",
				//"../ThirdParty",
			);
			return $sArray;
		}

		public function GetDependancyArray()
		{
			$sArray = array(
				//"Shared",
				//"ThirdParty",
			);

			return $sArray;
		}
	}
?>
