/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 */
 
#include <cstring>
#include <map>
#include <ne_uri.h> 
#include "utilspriv.h"

using namespace std;
using namespace MusicBrainz;

string
MusicBrainz::intToString(const int i)
{
	char temp[32];
	sprintf(temp, "%d", i);
	return string(temp);
}

int
MusicBrainz::stringToInt(const std::string &s)
{
	return atoi(s.c_str());
}

string
MusicBrainz::uriEscape(const string &uri)
{
	char *esc_uri_str = ne_path_escape(uri.c_str());
	string esc_uri = string((const char *)esc_uri_str);
	free(esc_uri_str);
	return esc_uri;
}

string
MusicBrainz::urlEncode(const vector<pair<string, string> > &params)
{
	string encodedStr;
	bool first = true;	
	for (vector<pair<string, string> >::const_iterator i = params.begin(); i != params.end(); i++) {
		string name = i->first;
		string value = i->second;
		if (first)
			first = false;
		else
			encodedStr += "&";
		encodedStr += name + "=" + uriEscape(value);
	}
	return encodedStr;
}

