#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include "cct.h"

int main(int argc, char *argv[]){
	
	char cantidad[13]="0";
	char monedaDestino[10]="0", monedaOrigen[10]="0";
	char pLink[1000]="h";
	FILE *pArchivo;
	FILE *pDatos;
	char *dir="data.txt";
	char busca[20000]="0";
	char texto[20]="0";
	char tanteo='>';
	int i,temp,posIni,posFin;
	CURL *curl;
	
	/****************Primera parte**************/
	if(argc==2 && strcmp(argv[1],"--help")==0)
	{
		helpMsg();
		return 0;
	}
	else if(argc==2 && strcmp(argv[1],"--info")==0)
	{
		infoMsg();
		return 0;
	}
	if(argc==4)
	{
		for(i=0;i<strlen(argv[1]);i++)
		{
			if(isdigit(argv[1][i])!=0)
				cantidad[i]=argv[1][i];
		}
		for(i=0;i<strlen(argv[2]);i++)
		{
			monedaOrigen[i]=argv[2][i];
		}
		for(i=0;i<strlen(argv[3]);i++)
		{
			monedaDestino[i]=argv[3][i];
		}
	}
	else
	{
		badArgs();
		return 0;
	}
	
	concatenarLink(pLink,a,cantidad,b,monedaOrigen,c,monedaDestino);
	
	pArchivo=fopen(dir,"r");
	
	/****************Segunda parte**************/
	pDatos=fopen(dir,"w");

	curl = curl_easy_init();
	cURLfuncion(pDatos,pLink);
	curl_easy_cleanup(curl);
	
	fclose(pDatos);
	
	/**Pasar texto a arreglo**/
	crearArrayBusca(pArchivo,busca);
	
	/**Buscar numero**/
	for(i=0;i<sizeof(busca);i++)
	{
		if(busca[i]==tanteo)
		{
			temp=i;
			if(busca[temp-1]=='d' && busca[temp-2]=='l' && busca[temp-3]=='b')
				posIni=temp+1;
		}
		
		if(busca[i]==monedaDestino[0] && busca[i+1]==monedaDestino[1] && busca[i+2]==monedaDestino[2])
		{
			posFin=i-1;
		}
	}
	
	/**Pasar numero a arreglo**/
	resultadoEncontrado(busca,texto,posIni,posFin);
	
	/**Imprimir resultado**/
	printf("\n%s %s = %s %s\n\n",cantidad,monedaOrigen,texto,monedaDestino);
	
	fclose(pArchivo);
	
	return 0;
}

char concatenarLink (char *pLink, char *a, char *cantidad, char *b, char *monedaOrigen, char *c, char *monedaDestino)
{
	int i;
	
	for(i=0;i<strlen(monedaOrigen);i++)
	{
		monedaOrigen[i]=toupper(monedaOrigen[i]);
	}
	
	for(i=0;i<strlen(monedaDestino);i++)
	{
		monedaDestino[i]=toupper(monedaDestino[i]);
	}
		
	strcat(pLink,a);
	strcat(pLink,cantidad);
	strcat(pLink,b);
	strcat(pLink,monedaOrigen);
	strcat(pLink,c);
	strcat(pLink,monedaDestino);
	return *pLink;
}

void cURLfuncion(FILE *pDatos, char *pLink)
{
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, pLink);
		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, pDatos);
		
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		
		return;
	}
}

char *crearArrayBusca (FILE *pArchivo, char *busca)
{
	int i=0,ch;
	ch=getc(pArchivo);
	while(ch!=EOF)
	{
		busca[i]=ch;
		ch=getc(pArchivo);
		i++;
	}
	return busca;
}

char *resultadoEncontrado (char *busca, char *texto, int posIni, int posFin)
{
	int i,j=0;

	for(i=posIni;i<posFin;i++)
	{
		texto[j]=busca[i];
		j++;
	}	
	return texto;
}

void helpMsg (void)
{
	printf("\n# Description\n");
	printf("\tCCT is a lightweight and powerful tool that uses Google Finance API to perform currency conversions directly from the console.\n\n");
	printf("# Syntax\n");
	printf("\tcct <amount_to_convert> <currency_origin> <currency_destination>\n\n");
	printf("# Examples\n");
	printf("\tcct 20 usd eur (convert dollar to euro)\n");
	printf("\tcct 5 ARS usd (convert argentine peso to dollar)\n\n");
	printf("NOTE: Supported words are lowercase or uppercase.\n\n");
	printf("# Supported currencies\n");
	printf("\t\"AED\" - United Arab Emirates Dirham (AED)\n");
	printf("\t\"AFN\" - Afghan Afghani (AFN)\n");
	printf("\t\"ALL\" - Albanian Lek (ALL)\n");
	printf("\t\"AMD\" - Armenian Dram (AMD)\n");
	printf("\t\"ANG\" - Netherlands Antillean Guilder (ANG)\n");
	printf("\t\"AOA\" - Angolan Kwanza (AOA)\n");
	printf("\t\"ARS\" - Argentine Peso (ARS)\n");
	printf("\t\"AUD\" - Australian Dollar (A$)\n");
	printf("\t\"AWG\" - Aruban Florin (AWG)\n");
	printf("\t\"AZN\" - Azerbaijani Manat (AZN)\n");
	printf("\t\"BAM\" - Bosnia-Herzegovina Convertible Mark (BAM)\n");
	printf("\t\"BBD\" - Barbadian Dollar (BBD)\n");
	printf("\t\"BDT\" - Bangladeshi Taka (BDT)\n");
	printf("\t\"BGN\" - Bulgarian Lev (BGN)\n");
	printf("\t\"BHD\" - Bahraini Dinar (BHD)\n");
	printf("\t\"BIF\" - Burundian Franc (BIF)\n");
	printf("\t\"BMD\" - Bermudan Dollar (BMD)\n");
	printf("\t\"BND\" - Brunei Dollar (BND)\n");
	printf("\t\"BOB\" - Bolivian Boliviano (BOB)\n");
	printf("\t\"BRL\" - Brazilian Real (R$)\n");
	printf("\t\"BSD\" - Bahamian Dollar (BSD)\n");
	printf("\t\"BTC\" - Bitcoin (฿)\n");
	printf("\t\"BTN\" - Bhutanese Ngultrum (BTN)\n");
	printf("\t\"BWP\" - Botswanan Pula (BWP)\n");
	printf("\t\"BYR\" - Belarusian Ruble (BYR)\n");
	printf("\t\"BZD\" - Belize Dollar (BZD)\n");
	printf("\t\"CAD\" - Canadian Dollar (CA$)\n");
	printf("\t\"CDF\" - Congolese Franc (CDF)\n");
	printf("\t\"CHF\" - Swiss Franc (CHF)\n");
	printf("\t\"CLF\" - Chilean Unit of Account (UF) (CLF)\n");
	printf("\t\"CLP\" - Chilean Peso (CLP)\n");
	printf("\t\"CNH\" - CNH (CNH)\n");
	printf("\t\"CNY\" - Chinese Yuan (CN¥)\n");
	printf("\t\"COP\" - Colombian Peso (COP)\n");
	printf("\t\"CRC\" - Costa Rican Colón (CRC)\n");
	printf("\t\"CUP\" - Cuban Peso (CUP)\n");
	printf("\t\"CVE\" - Cape Verdean Escudo (CVE)\n");
	printf("\t\"CZK\" - Czech Republic Koruna (CZK)\n");
	printf("\t\"DEM\" - German Mark (DEM)\n");
	printf("\t\"DJF\" - Djiboutian Franc (DJF)\n");
	printf("\t\"DKK\" - Danish Krone (DKK)\n");
	printf("\t\"DOP\" - Dominican Peso (DOP)\n");
	printf("\t\"DZD\" - Algerian Dinar (DZD)\n");
	printf("\t\"EGP\" - Egyptian Pound (EGP)\n");
	printf("\t\"ERN\" - Eritrean Nakfa (ERN)\n");
	printf("\t\"ETB\" - Ethiopian Birr (ETB)\n");
	printf("\t\"EUR\" - Euro (€)\n");
	printf("\t\"FIM\" - Finnish Markka (FIM)\n");
	printf("\t\"FJD\" - Fijian Dollar (FJD)\n");
	printf("\t\"FKP\" - Falkland Islands Pound (FKP)\n");
	printf("\t\"FRF\" - French Franc (FRF)\n");
	printf("\t\"GBP\" - British Pound (£)\n");
	printf("\t\"GEL\" - Georgian Lari (GEL)\n");
	printf("\t\"GHS\" - Ghanaian Cedi (GHS)\n");
	printf("\t\"GIP\" - Gibraltar Pound (GIP)\n");
	printf("\t\"GMD\" - Gambian Dalasi (GMD)\n");
	printf("\t\"GNF\" - Guinean Franc (GNF)\n");
	printf("\t\"GTQ\" - Guatemalan Quetzal (GTQ)\n");
	printf("\t\"GYD\" - Guyanaese Dollar (GYD)\n");
	printf("\t\"HKD\" - Hong Kong Dollar (HK$)\n");
	printf("\t\"HNL\" - Honduran Lempira (HNL)\n");
	printf("\t\"HRK\" - Croatian Kuna (HRK)\n");
	printf("\t\"HTG\" - Haitian Gourde (HTG)\n");
	printf("\t\"HUF\" - Hungarian Forint (HUF)\n");
	printf("\t\"IDR\" - Indonesian Rupiah (IDR)\n");
	printf("\t\"IEP\" - Irish Pound (IEP)\n");
	printf("\t\"ILS\" - Israeli New Sheqel (₪)\n");
	printf("\t\"INR\" - Indian Rupee (Rs.)\n");
	printf("\t\"IQD\" - Iraqi Dinar (IQD)\n");
	printf("\t\"IRR\" - Iranian Rial (IRR)\n");
	printf("\t\"ISK\" - Icelandic Króna (ISK)\n");
	printf("\t\"ITL\" - Italian Lira (ITL)\n");
	printf("\t\"JMD\" - Jamaican Dollar (JMD)\n");
	printf("\t\"JOD\" - Jordanian Dinar (JOD)\n");
	printf("\t\"JPY\" - Japanese Yen (¥)\n");
	printf("\t\"KES\" - Kenyan Shilling (KES)\n");
	printf("\t\"KGS\" - Kyrgystani Som (KGS)\n");
	printf("\t\"KHR\" - Cambodian Riel (KHR)\n");
	printf("\t\"KMF\" - Comorian Franc (KMF)\n");
	printf("\t\"KPW\" - North Korean Won (KPW)\n");
	printf("\t\"KRW\" - South Korean Won (₩)\n");
	printf("\t\"KWD\" - Kuwaiti Dinar (KWD)\n");
	printf("\t\"KYD\" - Cayman Islands Dollar (KYD)\n");
	printf("\t\"KZT\" - Kazakhstani Tenge (KZT)\n");
	printf("\t\"LAK\" - Laotian Kip (LAK)\n");
	printf("\t\"LBP\" - Lebanese Pound (LBP)\n");
	printf("\t\"LKR\" - Sri Lankan Rupee (LKR)\n");
	printf("\t\"LRD\" - Liberian Dollar (LRD)\n");
	printf("\t\"LSL\" - Lesotho Loti (LSL)\n");
	printf("\t\"LTL\" - Lithuanian Litas (LTL)\n");
	printf("\t\"LVL\" - Latvian Lats (LVL)\n");
	printf("\t\"LYD\" - Libyan Dinar (LYD)\n");
	printf("\t\"MAD\" - Moroccan Dirham (MAD)\n");
	printf("\t\"MDL\" - Moldovan Leu (MDL)\n");
	printf("\t\"MGA\" - Malagasy Ariary (MGA)\n");
	printf("\t\"MKD\" - Macedonian Denar (MKD)\n");
	printf("\t\"MMK\" - Myanmar Kyat (MMK)\n");
	printf("\t\"MNT\" - Mongolian Tugrik (MNT)\n");
	printf("\t\"MOP\" - Macanese Pataca (MOP)\n");
	printf("\t\"MRO\" - Mauritanian Ouguiya (MRO)\n");
	printf("\t\"MUR\" - Mauritian Rupee (MUR)\n");
	printf("\t\"MVR\" - Maldivian Rufiyaa (MVR)\n");
	printf("\t\"MWK\" - Malawian Kwacha (MWK)\n");
	printf("\t\"MXN\" - Mexican Peso (MX$)\n");
	printf("\t\"MYR\" - Malaysian Ringgit (MYR)\n");
	printf("\t\"MZN\" - Mozambican Metical (MZN)\n");
	printf("\t\"NAD\" - Namibian Dollar (NAD)\n");
	printf("\t\"NGN\" - Nigerian Naira (NGN)\n");
	printf("\t\"NIO\" - Nicaraguan Córdoba (NIO)\n");
	printf("\t\"NOK\" - Norwegian Krone (NOK)\n");
	printf("\t\"NPR\" - Nepalese Rupee (NPR)\n");
	printf("\t\"NZD\" - New Zealand Dollar (NZ$)\n");
	printf("\t\"OMR\" - Omani Rial (OMR)\n");
	printf("\t\"PAB\" - Panamanian Balboa (PAB)\n");
	printf("\t\"PEN\" - Peruvian Nuevo Sol (PEN)\n");
	printf("\t\"PGK\" - Papua New Guinean Kina (PGK)\n");
	printf("\t\"PHP\" - Philippine Peso (Php)\n");
	printf("\t\"PKG\" - PKG (PKG)\n");
	printf("\t\"PKR\" - Pakistani Rupee (PKR)\n");
	printf("\t\"PLN\" - Polish Zloty (PLN)\n");
	printf("\t\"PYG\" - Paraguayan Guarani (PYG)\n");
	printf("\t\"QAR\" - Qatari Rial (QAR)\n");
	printf("\t\"RON\" - Romanian Leu (RON)\n");
	printf("\t\"RSD\" - Serbian Dinar (RSD)\n");
	printf("\t\"RUB\" - Russian Ruble (RUB)\n");
	printf("\t\"RWF\" - Rwandan Franc (RWF)\n");
	printf("\t\"SAR\" - Saudi Riyal (SAR)\n");
	printf("\t\"SBD\" - Solomon Islands Dollar (SBD)\n");
	printf("\t\"SCR\" - Seychellois Rupee (SCR)\n");
	printf("\t\"SDG\" - Sudanese Pound (SDG)\n");
	printf("\t\"SEK\" - Swedish Krona (SEK)\n");
	printf("\t\"SGD\" - Singapore Dollar (SGD)\n");
	printf("\t\"SHP\" - St. Helena Pound (SHP)\n");
	printf("\t\"SKK\" - Slovak Koruna (SKK)\n");
	printf("\t\"SLL\" - Sierra Leonean Leone (SLL)\n");
	printf("\t\"SOS\" - Somali Shilling (SOS)\n");
	printf("\t\"SRD\" - Surinamese Dollar (SRD)\n");
	printf("\t\"STD\" - São Tomé & Príncipe Dobra (STD)\n");
	printf("\t\"SVC\" - Salvadoran Colón (SVC)\n");
	printf("\t\"SYP\" - Syrian Pound (SYP)\n");
	printf("\t\"SZL\" - Swazi Lilangeni (SZL)\n");
	printf("\t\"THB\" - Thai Baht (THB)\n");
	printf("\t\"TJS\" - Tajikistani Somoni (TJS)\n");
	printf("\t\"TMT\" - Turkmenistani Manat (TMT)\n");
	printf("\t\"TND\" - Tunisian Dinar (TND)\n");
	printf("\t\"TOP\" - Tongan Pa´anga (TOP)\n");
	printf("\t\"TRY\" - Turkish Lira (TRY)\n");
	printf("\t\"TTD\" - Trinidad & Tobago Dollar (TTD)\n");
	printf("\t\"TWD\" - New Taiwan Dollar (NT$)\n");
	printf("\t\"TZS\" - Tanzanian Shilling (TZS)\n");
	printf("\t\"UAH\" - Ukrainian Hryvnia (UAH)\n");
	printf("\t\"UGX\" - Ugandan Shilling (UGX)\n");
	printf("\t\"USD\" - US Dollar ($)\n");
	printf("\t\"UYU\" - Uruguayan Peso (UYU)\n");
	printf("\t\"UZS\" - Uzbekistani Som (UZS)\n");
	printf("\t\"VEF\" - Venezuelan Bolívar (VEF)\n");
	printf("\t\"VND\" - Vietnamese Dong (₫)\n");
	printf("\t\"VUV\" - Vanuatu Vatu (VUV)\n");
	printf("\t\"WST\" - Samoan Tala (WST)\n");
	printf("\t\"XAF\" - Central African CFA Franc (FCFA)\n");
	printf("\t\"XCD\" - East Caribbean Dollar (EC$)\n");
	printf("\t\"XDR\" - Special Drawing Rights (XDR)\n");
	printf("\t\"XOF\" - West African CFA Franc (CFA)\n");
	printf("\t\"XPF\" - CFP Franc (CFPF)\n");
	printf("\t\"YER\" - Yemeni Rial (YER)\n");
	printf("\t\"ZAR\" - South African Rand (ZAR)\n");
	printf("\t\"ZMK\" - Zambian Kwacha (1968-2012) (ZMK)\n");
	printf("\t\"ZMW\" - Zambian Kwacha (ZMW)\n");
	printf("\t\"ZWL\" - Zimbabwean Dollar (2009) (ZWL)\n\n");
}

void infoMsg (void)
{
	printf("\t\t   ______    ______  _________  \n");
	printf("\t\t .' ___  | .' ___  ||  _   _  | \n");
	printf("\t\t/ .'   \\_|/ .'   \\_||_/ | | \\_| \n");
	printf("\t\t| |       | |           | |     \n");
	printf("\t\t\\ `.___.'\\\\ `.___.'\\   _| |_    \n");
	printf("\t\t `.____ .' `.____ .'  |_____|   \n");
	printf("\t\t                                \n");
	printf("\t\t# Currency Convert Tool v1.0\n\n");
	printf("# Developed by Maximiliano Ferrer Gregori\n");
	printf("# Contact me: maxi.fg@opmbx.org \n\n");
}

void badArgs (void)
{
	printf("cct: few arguments\n");
	printf("Try 'cct --help' for more information or look at the information of the program with 'cct --info'.\n");
}
