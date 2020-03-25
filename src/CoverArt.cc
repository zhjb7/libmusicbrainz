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

#include "musicbrainz5/CoverArt.h"

class MusicBrainz5::CCoverArtPrivate
{
	public:
		CCoverArtPrivate():m_Count(0)
		{
		}
		std::string m_Artwork;
		int m_Count;
		std::string m_Front;
		std::string m_Back;
};

MusicBrainz5::CCoverArt::CCoverArt(const XMLNode& Node)
:	CEntity(),
	m_d(new CCoverArtPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CoverArt node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CCoverArt::CCoverArt(const CCoverArt& Other)
:	CEntity(),
	m_d(new CCoverArtPrivate)
{
	*this=Other;
}

MusicBrainz5::CCoverArt& MusicBrainz5::CCoverArt::operator =(const CCoverArt& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Artwork=Other.m_d->m_Artwork;
		m_d->m_Count=Other.m_d->m_Count;
		m_d->m_Front=Other.m_d->m_Front;
		m_d->m_Back=Other.m_d->m_Back;
	}

	return *this;
}

MusicBrainz5::CCoverArt::~CCoverArt()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CCoverArt::Cleanup()
{

}

MusicBrainz5::CCoverArt *MusicBrainz5::CCoverArt::Clone()
{
	return new CCoverArt(*this);
}

void MusicBrainz5::CCoverArt::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised coverart attribute: '" << Name << "'" << std::endl;
#else
	(void)Name;
#endif
}

void MusicBrainz5::CCoverArt::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("artwork"==NodeName)
	{
		ProcessItem(Node,m_d->m_Artwork);
	}
	else if ("count"==NodeName)
	{
		ProcessItem(Node,m_d->m_Count);
	}
	else if ("front"==NodeName)
	{
		ProcessItem(Node,m_d->m_Front);
	}
	else if ("back"==NodeName)
	{
		ProcessItem(Node,m_d->m_Back);
	}
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised coverart element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CCoverArt::GetElementName()
{
	return "cover-art-archive";
}

std::string MusicBrainz5::CCoverArt::Artwork() const
{
	return m_d->m_Artwork;
}

int MusicBrainz5::CCoverArt::Count() const
{
	return m_d->m_Count;
}

std::string MusicBrainz5::CCoverArt::Front() const
{
	return m_d->m_Front;
}

std::string MusicBrainz5::CCoverArt::Back() const
{
	return m_d->m_Back;
}

std::ostream& MusicBrainz5::CCoverArt::Serialise(std::ostream& os) const
{
	os << "CoverArt:" << std::endl;

	CEntity::Serialise(os);

	os << "Artwork: " << Artwork() << std::endl;
	os << "Count:  " << Count() << std::endl;
	os << "Front: " << Front() << std::endl;
	os << "Back: " << Back() << std::endl;

	return os;
}
