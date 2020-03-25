/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/Genre.h"

class MusicBrainz5::CGenrePrivate
{
	public:
		CGenrePrivate():m_Count(0)
		{
		}
		int m_Count;
		std::string m_GenreName;
};

MusicBrainz5::CGenre::CGenre(const XMLNode& Node)
:	CEntity(),
	m_d(new CGenrePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Genre node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CGenre::CGenre(const CGenre& Other)
:	CEntity(),
	m_d(new CGenrePrivate)
{
	*this=Other;
}

MusicBrainz5::CGenre& MusicBrainz5::CGenre::operator =(const CGenre& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Count=Other.m_d->m_Count;
		m_d->m_GenreName=Other.m_d->m_GenreName;
	}

	return *this;
}

MusicBrainz5::CGenre::~CGenre()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CGenre::Cleanup()
{

}

MusicBrainz5::CGenre *MusicBrainz5::CGenre::Clone()
{
	return new CGenre(*this);
}

void MusicBrainz5::CGenre::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("count"==Name)
		ProcessItem(Value,m_d->m_Count);
	else
	{
		#ifdef _MB5_DEBUG_
			std::cerr << "Unrecognised genre attribute: '" << Name << "'" << std::endl;
		#else
	}
#endif
}

void MusicBrainz5::CGenre::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_GenreName);
	}
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised genre element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CGenre::GetElementName()
{
	return "genre";
}

int MusicBrainz5::CGenre::Count() const
{
	return m_d->m_Count;
}

std::string MusicBrainz5::CGenre::GenreName() const
{
	return m_d->m_GenreName;
}

std::ostream& MusicBrainz5::CGenre::Serialise(std::ostream& os) const
{
	os << "Genre:" << std::endl;

	CEntity::Serialise(os);

	os << "Count:  " << Count() << std::endl;
	os << "\tGenre Name: " << GenreName() << std::endl;

	return os;
}

