/***************************************************************************
 *   Copyright (C) 2008-2010 by Чернов А.А.                                *
 *   valexlin@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "cam_tables.h"
#include <string.h>
#include <stdlib.h>
//#include <stdio.h>

struct EOSAvTable AvTable[EOS_AV_TABLE_SZ] = {
	{ 0x00, "0" },
	{ 0x08, "1" },
	{ 0x0B, "1.1" },
	{ 0x0C, "1.2" },
	{ 0x0D, "1.2" },	// (1/3)
	{ 0x10, "1.4" },
	{ 0x13, "1.6" },
	{ 0x14, "1.8" },
	{ 0x15, "1.8" },	// (1/3)
	{ 0x18, "2" },
	{ 0x1B, "2.2" },
	{ 0x1C, "2.5" },
	{ 0x1D, "2.5" },	// (1/3)
	{ 0x20, "2.8" },
	{ 0x23, "3.2" },
	{ 0x24, "3.5" },
	{ 0x25, "3.5" },	// (1/3)
	{ 0x28, "4" },
	{ 0x2B, "4.5" },
	{ 0x2C, "4.5" },	// (1/3)
	{ 0x2D, "5.0" },
	{ 0x30, "5.6" },
	{ 0x33, "6.3" },
	{ 0x34, "6.7" },
	{ 0x35, "7.1" },
	{ 0x38, "8" },
	{ 0x3B, "9" },
	{ 0x3C, "9.5" },
	{ 0x3D, "10" },
	{ 0x40, "11" },
	{ 0x43, "13" },
	{ 0x44, "13" },
	{ 0x45, "14" },
	{ 0x48, "16" },
	{ 0x4B, "18" },
	{ 0x4C, "19" },
	{ 0x4D, "20" },
	{ 0x50, "22" },
	{ 0x53, "25" },
	{ 0x54, "27" },
	{ 0x55, "29" },
	{ 0x58, "32" },
	{ 0x5B, "36" },
	{ 0x5C, "38" },
	{ 0x5D, "40" },
	{ 0x60, "45" },
	{ 0x63, "51" },
	{ 0x64, "54" },
	{ 0x65, "57" },
	{ 0x68, "64" },
	{ 0x6B, "72" },
	{ 0x6C, "76" },
	{ 0x6D, "80" },
	{ 0x70, "91" },
	{ 0xffffffff, "Err" }
};

struct EOSTvTable TvTable[EOS_TV_TABLE_SZ] = {
	//{ 0x0C, "Bulb" },
	{ 0x10, "30\"", "30" },
	{ 0x13, "25\"", "25" },
	{ 0x14, "20\"", "20" },
	{ 0x15, "20\"", "20" },
	{ 0x18, "15\"", "15" },
	{ 0x1B, "13\"", "13" },
	{ 0x1C, "10\"", "10" },
	{ 0x1D, "10\"", "10" },	// (1/3)
	{ 0x20, "8\"", "8" },
	{ 0x23, "6\"", "6" },	// (1/3)
	{ 0x24, "6\"", "6" },
	{ 0x25, "5\"", "5" },
	{ 0x28, "4\"", "4" },
	{ 0x2B, "3\"2", "3.2" },
	{ 0x2C, "3\"", "3" },
	{ 0x2D, "2\"5", "2.5" },
	{ 0x30, "2\"", "2" },
	{ 0x33, "1\"6", "1.6" },
	{ 0x34, "1\"5", "1.5" },
	{ 0x35, "1\"3", "1.3" },
	{ 0x38, "1\"", "1" },
	{ 0x3B, "0\"8", "0.8" },
	{ 0x3C, "0\"7", "0.7" },
	{ 0x3D, "0\"6", "0.6" },
	{ 0x40, "0\"5", "0.5" },
	{ 0x43, "0\"4", "0.4" },
	{ 0x44, "0\"3", "0.3" },
	{ 0x45, "0\"3", "0.3" },	// (1/3)
	{ 0x48, "1/4", "1/4" },
	{ 0x4B, "1/5", "1/5" },
	{ 0x4C, "1/6", "1/6" },
	{ 0x4D, "1/6", "1/6" },	// (1/3)
	{ 0x50, "1/8", "1/8" },
	{ 0x53, "1/10", "1/10" },	// (1/3)
	{ 0x54, "1/10", "1/10" },
	{ 0x55, "1/13", "1/13" },
	{ 0x58, "1/15", "1/15" },
	{ 0x5B, "1/20", "1/20" },	// (1/3)
	{ 0x5C, "1/20", "1/20" },
	{ 0x5D, "1/25", "1/25" },
	{ 0x60, "1/30", "1/30" },
	{ 0x63, "1/40", "1/40" },
	{ 0x64, "1/45", "1/45" },
	{ 0x65, "1/50", "1/50" },
	{ 0x68, "1/60", "1/60" },
	{ 0x6B, "1/80", "1/80" },
	{ 0x6C, "1/90", "1/90" },
	{ 0x6D, "1/100", "1/100" },
	{ 0x70, "1/125", "1/125" },
	{ 0x73, "1/160", "1/160" },
	{ 0x74, "1/180", "1/180" },
	{ 0x75, "1/200", "1/200" },
	{ 0x78, "1/250", "1/250" },
	{ 0x7B, "1/320", "1/320" },
	{ 0x7C, "1/350", "1/350" },
	{ 0x7D, "1/400", "1/400" },
	{ 0x80, "1/500", "1/500" },
	{ 0x83, "1/640", "1/640" },
	{ 0x84, "1/750", "1/750" },
	{ 0x85, "1/800", "1/800" },
	{ 0x88, "1/1000", "1/1000" },
	{ 0x8B, "1/1250", "1/1250" },
	{ 0x8C, "1/1500", "1/1500" },
	{ 0x8D, "1/1600", "1/1600" },
	{ 0x90, "1/2000", "1/2000" },
	{ 0x93, "1/2500", "1/2500" },
	{ 0x94, "1/3000", "1/3000" },
	{ 0x95, "1/3200", "1/3200" },
	{ 0x98, "1/4000", "1/4000" },
	{ 0x9B, "1/5000", "1/5000" },
	{ 0x9C, "1/6000", "1/6000" },
	{ 0x9D, "1/6400", "1/6400" },
	{ 0xA0, "1/8000", "1/8000" },
	{ 0xffffffff, "Err", "Err" }
};

struct EOSISOTable ISOTable[EOS_ISO_TABLE_SZ] = {
	{ 0x28, "6" },
	{ 0x30, "12" },
	{ 0x38, "25" },
	{ 0x40, "50" },
	{ 0x48, "100" },
	{ 0x4b, "125" },
	{ 0x4d, "160" },
	{ 0x50, "200" },
	{ 0x53, "250" },
	{ 0x55, "320" },
	{ 0x58, "400" },
	{ 0x5b, "500" },
	{ 0x5d, "640" },
	{ 0x60, "800" },
	{ 0x63, "1000" },
	{ 0x65, "1250" },
	{ 0x68, "1600" },
	{ 0x70, "3200" },
	{ 0x78, "6400" },
	{ 0x80, "12800" },
	{ 0x88, "25600" },
	{ 0xffffffff, "Err" }
};

struct EOSAEMTable AEMTable[EOS_AEM_TABLE_SZ] = {
	{ 0x00, "P", "P" },
	{ 0x01, "TV", "Tv" },
	{ 0x02, "AV", "Av" },
	{ 0x03, "Manual", "M" },
	{ 0x05, "A_DEP", "A-DEP" },
	{ 0xffffffff, "Err" }
};

int findAV_edsdk(int edsdk_val)
{
	register int i;
	register int res = EOS_AV_TABLE_SZ - 1;
	for (i = 0; i < EOS_AV_TABLE_SZ; i++)
	{
		if (edsdk_val == AvTable[i].edsdk_val)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findAV_str(const char* str)
{
	register int i;
	register int res = EOS_AV_TABLE_SZ - 1;
	char str1[4];
	char str2[4];
	size_t len;
	strncpy(str1, str, 3);
	str1[3] = 0;
	len = strlen(str1);
	if (len == 3)
	{
		if (str1[1] == '.' && str1[2] == '0')
			str1[1] = 0;
	}
	for (i = 0; i < EOS_AV_TABLE_SZ; i++)
	{
		strncpy(str2, AvTable[i].av, 3);
		str2[3] = 0;
		len = strlen(str2);
		if (len == 3)
		{
			if (str2[1] == '.' && str2[2] == '0')
				str2[1] = 0;
		}
		if (strcmp(str1, str2) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findTV_edsdk(int edsdk_val)
{
	register int i;
	register int res = EOS_TV_TABLE_SZ - 1;
	for (i = 0; i < EOS_TV_TABLE_SZ; i++)
	{
		if (edsdk_val == TvTable[i].edsdk_val)
		{
			res = i;
			break;
		}
	}
	return res;
}

#if 0
static char* convert_tv_gp2_to_edsdk(const char* tv)
{
	int len = strlen(tv);
	char* str = (char*)malloc(len + 2);
	const char* sptr = tv;
	char* dptr = (char*)str;
	int need_quote = 1;
	while (*sptr)
	{
		if (*sptr == '.' || *sptr == ',')
		{
			*dptr = '\"';
			need_quote = 0;
		}
		else
			*dptr = *sptr;
		if (*sptr == '/')
			need_quote = 0;
		sptr++;
		dptr++;
	}
	if (need_quote)
	{
		*dptr = '\"';
		dptr++;
	}
	*dptr = 0;
	return str;
}
#endif

int findTV_str(const char* str)
{
	register int i;
	register int res = EOS_TV_TABLE_SZ - 1;
	for (i = 0; i < EOS_TV_TABLE_SZ; i++)
	{
		if (strcmp(str, TvTable[i].tv) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findTV_gp2_str(const char* str)
{
	register int i;
	register int res = EOS_TV_TABLE_SZ - 1;
	//char* str_ed = convert_tv_gp2_to_edsdk(str);
	char* str_ed = strdup(str);
	char* ptr = str_ed;
	while (*ptr)
	{
		if (*ptr == ',')
			*ptr = '.';
		ptr++;
	}
	for (i = 0; i < EOS_TV_TABLE_SZ; i++)
	{
		if (strcmp(str_ed, TvTable[i].gp2_tv) == 0)
		{
			res = i;
			break;
		}
	}
	free(str_ed);
	return res;
}

int findISO_edsdk(int edsdk_val)
{
	register int i;
	register int res = EOS_ISO_TABLE_SZ - 1;
	for (i = 0; i < EOS_ISO_TABLE_SZ; i++)
	{
		if (edsdk_val == ISOTable[i].edsdk_val)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findISO_str(const char* str)
{
	register int i;
	register int res = EOS_ISO_TABLE_SZ - 1;
	for (i = 0; i < EOS_ISO_TABLE_SZ; i++)
	{
		if (strcmp(str, ISOTable[i].ISO) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findAEM_edsdk(int edsdk_val)
{
	register int i;
	register int res = EOS_AEM_TABLE_SZ - 1;
	for (i = 0; i < EOS_AEM_TABLE_SZ; i++)
	{
		if (edsdk_val == AEMTable[i].edsdk_val)
		{
			res = i;
			break;
		}
	}
	return res;
}

int findAEM_str(const char* str)
{
	register int i;
	register int res = EOS_AEM_TABLE_SZ - 1;
	for (i = 0; i < EOS_AEM_TABLE_SZ; i++)
	{
		if (strcmp(str, AEMTable[i].gphoto_str) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}
