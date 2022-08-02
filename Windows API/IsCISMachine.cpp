BOOL IsCISMachine()
{
	LANGID UserDefaultUILang = GetUserDefaultUILanguage();
	LANGID SystemDefaultLang = GetSystemDefaultLangID();
	LANGID UserDefaultLangID = GetUserDefaultLangID();
	
	static LANGID CIS_countries[] =
	{
		SUBLANG_RUSSIAN_RUSSIA,
		SUBLANG_UKRAINIAN_UKRAINE,
		SUBLANG_BELARUSIAN_BELARUS,
		SUBLANG_TAJIK_TAJIKISTAN,
		SUBLANG_ARMENIAN_ARMENIA,
		SUBLANG_AZERI_LATIN,
		SUBLANG_GEORGIAN_GEORGIA,
		SUBLANG_KAZAK_KAZAKHSTAN,
		SUBLANG_KYRGYZ_KYRGYZSTAN,
		SUBLANG_TURKISH_TURKEY,
		SUBLANG_UZBEK_LATIN, 
		SUBLANG_TATAR_RUSSIA, 
		SUBLANG_ROMANIAN_ROMANIA,
		SUBLANG_SAKHA_RUSSIA, 
		SUBLANG_AZERI_CYRILLIC, 
		SUBLANG_UZBEK_CYRILLIC
	};

	for( unsigned short i = 0; i < _countof( CIS_countries ); i++ )
	{
		if( CIS_countries[i] == UserDefaultUILang ||
			CIS_countries[i] == SystemDefaultLang ||
			CIS_countries[i] == UserDefaultLangID )
			return TRUE;
	}
	return FALSE;
}
