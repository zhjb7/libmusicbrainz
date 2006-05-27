#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

class ModelTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ModelTest);
	CPPUNIT_TEST(testDiscProperties);
	CPPUNIT_TEST(testArtistProperties);
	CPPUNIT_TEST(testTrackProperties);
	CPPUNIT_TEST(testReleaseEventProperties);
	CPPUNIT_TEST(testArtistAliasProperties);
	CPPUNIT_TEST(testUserTypes);
	CPPUNIT_TEST(testAddRelation);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testDiscProperties()
	{
		Disc a("X64QNQ5GVfJUFF9MKTe3AD0wbag-");
		a.setFirstTrackNum(1);
		a.setLastTrackNum(12);
		a.setSectors(260075);
		a.addTrack(Disc::Track(150, 19912));
		a.addTrack(Disc::Track(20062, 32335));
		CPPUNIT_ASSERT_EQUAL(string("X64QNQ5GVfJUFF9MKTe3AD0wbag-"), a.getId());
		CPPUNIT_ASSERT_EQUAL(1, a.getFirstTrackNum());
		CPPUNIT_ASSERT_EQUAL(12, a.getLastTrackNum());
		CPPUNIT_ASSERT_EQUAL(260075, a.getSectors());
		CPPUNIT_ASSERT_EQUAL(2, int(a.getTracks().size()));
		CPPUNIT_ASSERT_EQUAL(150, a.getTracks()[0].first);
		CPPUNIT_ASSERT_EQUAL(32335, a.getTracks()[1].second);
	}
	
	void testArtistProperties()
	{
		Artist a("86e2e2ad-6d1b-44fd-9463-b6683718a1cc", Artist::TYPE_PERSON, "Jean Michel Jarre", "Jarre, Jean Michel");
		CPPUNIT_ASSERT_EQUAL(string("86e2e2ad-6d1b-44fd-9463-b6683718a1cc"), a.getId());
		CPPUNIT_ASSERT_EQUAL(Artist::TYPE_PERSON, a.getType());
		CPPUNIT_ASSERT_EQUAL(string("Jean Michel Jarre"), a.getName());
		CPPUNIT_ASSERT_EQUAL(string("Jarre, Jean Michel"), a.getSortName());
		Artist b;
		b.setId("86e2e2ad-6d1b-44fd-9463-b6683718a1cc");
		b.setType(Artist::TYPE_PERSON);
		b.setName("Jean Michel Jarre");
		b.setSortName("Jarre, Jean Michel");
		b.setBeginDate("1948-08-24");
		b.setEndDate("1948-08-25");
		CPPUNIT_ASSERT_EQUAL(string("86e2e2ad-6d1b-44fd-9463-b6683718a1cc"), b.getId());
		CPPUNIT_ASSERT_EQUAL(Artist::TYPE_PERSON, b.getType());
		CPPUNIT_ASSERT_EQUAL(string("Jean Michel Jarre"), b.getName());
		CPPUNIT_ASSERT_EQUAL(string("Jarre, Jean Michel"), b.getSortName());
		CPPUNIT_ASSERT_EQUAL(string("1948-08-24"), b.getBeginDate());
		CPPUNIT_ASSERT_EQUAL(string("1948-08-25"), b.getEndDate());
	}
	
	void testTrackProperties()
	{
		Track a("8813e1f4-18a6-4cc2-b723-35da00af622d", "Aerozone");
		CPPUNIT_ASSERT_EQUAL(string("8813e1f4-18a6-4cc2-b723-35da00af622d"), a.getId());
		CPPUNIT_ASSERT_EQUAL(string("Aerozone"), a.getTitle());
		Track b;
		b.setId("8813e1f4-18a6-4cc2-b723-35da00af622d");
		b.setTitle("Aerozone");
		CPPUNIT_ASSERT_EQUAL(string("8813e1f4-18a6-4cc2-b723-35da00af622d"), b.getId());
		CPPUNIT_ASSERT_EQUAL(string("Aerozone"), b.getTitle());
	}
	
	void testReleaseEventProperties()
	{
		ReleaseEvent a("SK", "2006-05-26");
		CPPUNIT_ASSERT_EQUAL(string("SK"), a.getCountry());
		CPPUNIT_ASSERT_EQUAL(string("2006-05-26"), a.getDate());
		ReleaseEvent b;
		b.setCountry("SK");
		b.setDate("2006-05-26");
		CPPUNIT_ASSERT_EQUAL(string("SK"), b.getCountry());
		CPPUNIT_ASSERT_EQUAL(string("2006-05-26"), b.getDate());
	}
	
	void testArtistAliasProperties()
	{
		ArtistAlias a("小室哲哉", NS_MMD_1 + "Name", "Hrkt");
		CPPUNIT_ASSERT_EQUAL(string("小室哲哉"), a.getValue());
		CPPUNIT_ASSERT_EQUAL(NS_MMD_1 + string("Name"), a.getType());
		CPPUNIT_ASSERT_EQUAL(string("Hrkt"), a.getScript());
		ArtistAlias b;
		b.setValue("小室哲哉");
		b.setType(NS_MMD_1 + string("Name"));
		b.setScript("Hrkt");
		CPPUNIT_ASSERT_EQUAL(string("小室哲哉"), b.getValue());
		CPPUNIT_ASSERT_EQUAL(NS_MMD_1 + string("Name"), b.getType());
		CPPUNIT_ASSERT_EQUAL(string("Hrkt"), b.getScript());
	}
	
	void testAddRelation()
	{
		Relation *rel = new Relation("Producer", Relation::TO_RELEASE, "al_id");
		Artist artist("ar_id", "Tori Amos", Artist::TYPE_PERSON);
		artist.addRelation(rel);

		Relation *rel2 = artist.getRelations()[0];
		CPPUNIT_ASSERT_EQUAL(rel->getType(), rel2->getType());
		CPPUNIT_ASSERT_EQUAL(rel->getTargetType(), rel2->getTargetType());
		CPPUNIT_ASSERT_EQUAL(rel->getTargetId(), rel2->getTargetId());
		CPPUNIT_ASSERT_EQUAL(rel->getAttributes().size(), rel2->getAttributes().size());
		CPPUNIT_ASSERT_EQUAL(rel->getBeginDate(), rel2->getBeginDate());
		CPPUNIT_ASSERT_EQUAL(rel->getEndDate(), rel2->getEndDate());
	}
	
	void testUserTypes()
	{
		User a;
		a.addType(NS_MMD_1 + "AutoEditor");
		a.addType(NS_MMD_1 + "NotNaggable");
		CPPUNIT_ASSERT_EQUAL(2, int(a.getTypes().size()));
		CPPUNIT_ASSERT_EQUAL(NS_MMD_1 + "NotNaggable", a.getTypes()[1]);
	}	
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(ModelTest); 

